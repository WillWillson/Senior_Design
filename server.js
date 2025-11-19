if (process.env.NODE_ENV !== 'production') {
    require('dotenv').config()
}

const express = require('express')
const app = express()
const bcrypt = require('bcryptjs')
const passport = require('passport')
const flash = require('express-flash')
const session = require('express-session')
const methodOverride = require('method-override')
const fileUpload = require('express-fileupload')
const path = require('path')
const filesPayloadExists = require('./middleware/filesPayloadExists')
const fileExtLimiter = require('./middleware/fileExtLimiter')
const fileSizeLimiter = require('./middleware/fileSizeLimiter')
const fs = require('fs')


const PORT = process.env.PORT || 3000

const initializePassport = require('./passport-config')
initializePassport(
    passport, 
    username => users.find(user => user.username === username),
    id => users.find(user => user.id === id)
)

const users = []

app.set('view-engine', 'ejs')
app.use(express.urlencoded({ extended: false }))
app.use(flash())
app.use(session({
    secret: process.env.SESSION_SECRET,
    resave: false,
    saveUnitialized: false
}))
app.use(passport.initialize())
app.use(passport.session())
app.use(methodOverride('_method'))
app.use('/files', express.static(path.join(__dirname, 'files')))

app.get('/', checkAuthenticated, (req, res) => {
    res.render('index.ejs', { name: req.user.name})
})

app.post('/upload', 
    fileUpload({ createParentPath: true }),
    filesPayloadExists,
    fileExtLimiter(['.png', '.jpg', '.jpeg', '.txt']),
    fileSizeLimiter,
    (req, res) => {
        const files = req.files
        console.log(files)

        Object.keys(files).forEach(key => {
            const filepath = path.join(__dirname, 'files', files[key].name)
            files[key].mv(filepath, {recursive: true}, (err) => {
                if (err) return res.status(500).json({ status: "error", message: err })
            })
        })

        return res.json({ status: 'success', message: Object.keys(files).toString() })
    }
)

app.get('/files', (req, res) => {
   const file = fs.createWriteStream('CC.png')
   request = http.get('http://138.47.150.6:3000/files/CC.png', function(response) {
      response.pipe(file)
      file.on('finish', () => {
         file.close()
         console.log("Download Complete.")
      })
   }) 
})

app.get('/download', (req, res) => {
    const files = fs.readdirSync('files')
    res.render('download.ejs', {files: files})	
})

app.get('/login', checkNotAuthenticated, (req, res) => {
    res.render('login.ejs')
})

app.post('/login', checkNotAuthenticated, passport.authenticate('local', {
    successRedirect: '/',
    failureRedirect: '/login',
    failureFlash: true
}))

app.get('/register', checkNotAuthenticated, (req, res) => {
    res.render('register.ejs')
})

app.post('/register', checkNotAuthenticated, async (req, res) => {
    try {
        const hashedPassword = await bcrypt.hash(req.body.password, 10)
        users.push({
            id: Date.now().toString(),
            name: req.body.name,
            username: req.body.username,
            password: hashedPassword
        })
        res.redirect('/login')
    } catch {
        res.redirect('/register')
    }
    console.log(users)
})

app.delete('/logout', (req, res) => {
    req.logout(function(err) {
        if (err) { return next(err) }
        res.redirect('/login')
    })
   
})

function checkAuthenticated(req, res, next) {
    if (req.isAuthenticated()) {
        return next()
    }

    res.redirect('/login')
}

function checkNotAuthenticated(req, res, next) {
    if (req.isAuthenticated()) {
        return res.redirect('/')
    }
    next()
}

app.listen(PORT, () => console.log(`Server running on port ${PORT}`))
