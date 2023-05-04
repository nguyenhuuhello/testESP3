// https://github.com/Automattic/mongoose
const mongoose = require('mongoose');
require('dotenv').config();

async function connect(){ //await phải nằm trong 1 function async

    try {
        await mongoose.connect(process.env.MONGO_URI);
        console.log('Connect successfully!');
    } catch (error) {
        console.log('Connect failure!');
    }
}

// export như 1 object
module.exports = {connect};