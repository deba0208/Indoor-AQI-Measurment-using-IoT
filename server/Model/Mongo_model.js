
const mongoose = require("mongoose");


const componentSchema = new mongoose.Schema({

    co2: {
        type: Number,
        require: true
    },

    co: {
        type: Number,
        require: true
    },
    pm25: {
        type: Number,
        require: true
    },

    nh4: {
        type: Number,
        require: true
    },


    AQI: {
        type: Number,
        require: true
    },
    TVOC: {
        type: Number,
        require: true
    },

    Temperature: {
        type: Number,
        require: true
    },
    Humidity: {
        type: Number,
        require: true
    },



});

const componentModel = mongoose.model("ComponentData", componentSchema);


module.exports = componentModel; 