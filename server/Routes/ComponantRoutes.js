const express = require("express")
const app = express();
const product = require("../Model/Mongo_model")
app.use(express.json());


const router = express.Router();


router.post('/', async (req, res) => {

    try {

        const result = await product.create({

            

            
        })


        res.send(result)

        console.log("done");
    } catch (error) {
        res.send(error)
    }


});