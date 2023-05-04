const mongoose = require('mongoose');
const Schema = mongoose.Schema; //tạo model dữ liệu

const dataSchema = new Schema({
    led: {type: Boolean},
    createdAt: { type: Date, default: Date.now},
    updatedAt: { type: Date, default: Date.now},
});

module.exports = mongoose.model("dataSchema", dataSchema)