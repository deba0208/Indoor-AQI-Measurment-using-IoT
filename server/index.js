// server.js
//EyVc7dHpN9gtrzxa
//mongodb+srv://dasbabai2017:<password>@allcomponantvalue.226u6wj.mongodb.net/
const express = require("express");
const bodyParser = require("body-parser");
const fs = require("fs");
const { title } = require("process");
const cors = require("cors");
const mongoose = require("mongoose");
const { componentModel } = require("./Model/Mongo_model");
const app = express();
app.use(cors());
app.use(express.json());
const PORT = 3000;


// Ata dotenv file diye password er username neba ho66e
const dotenv = require('dotenv');
// const componentModel = require("./Model/Mongo_model");
dotenv.config();
const password = process.env.MONGO_PASSWORD;
const username = process.env.MONGO_USERNAME;

const authentication = (req, res, next) => {
  const auHeader = req.headers.Authentication;
  if (auHeader) {
    const token = auHeader.split(" ")[1];
    if (token === "123456789") {
      next();
    } else {
      res.json({ message: "forbidden" });
    }
  }
}
const component = (body) => {
  const comp = body.split(",");
  const newComps = {
    co2: Number(comp[0]),
    co: Number(comp[1]),
    nh4: Number(comp[2]),
    pm25: Number(comp[3]),
    TVOC: Number(comp[4]),
    AQI: Number(comp[5]),
    Temperature: Number(comp[6]),
    Humidity: Number(comp[7]),
  }
  return newComps;
}
// connecting to the mongo server
mongoose.connect(`mongodb+srv://${username}:${password}@allcomponantvalue.226u6wj.mongodb.net/`, {
  dbName: "AQI",

}).then((result) => {

  console.log("db connect");
}).catch((err) => {
  console.log(err);
});




app.get("/data", (req, res) => {
  fs.readFile("data.json", "utf-8", (err, data) => {
    if (err) throw err;
    res.status(200).json(JSON.parse(data));
  });
});
// app.post("/data", authentication, (req, res) => {
//   {
//     const creatNewEntry = {
//       id: Math.floor(Math.random() * 1000000),
//       date: req.body,
//     };
//     fs.readFile("data.json", "utf-8", (err, data) => {
//       if (err) throw err;
//       const entry = JSON.parse(data);
//       entry.push(creatNewEntry);
//       fs.writeFile("data.json", JSON.stringify(entry), (err) => {
//         if (err) throw err;
//         res.send(creatNewEntry);
//       });
//     });
//   } // else {
//   //   res.send("Error");
//   // }
//   // Process the data as needed
// });
// app.post("/data", async (req, res) => {
//   const values = component(req.body);
//   const newComp = new componentModel({ co2, co, nh4, pm25, TVOC, AQI, Temperature, Humidity });
//   await newComp.save();
//   res.json({ message: "successfully added" });
// })
app.post("/data", async (req, res) => {
  const val = (req.body);
  const { co2, co, nh4, pm25, TVOC, AQI, Temperature, Humidity } = req.body; // Destructure the properties from req.body
  console.log(req.body);
  // const newComp = await componentModel.create({ co2, co, nh4, pm25, TVOC, AQI, Temperature, Humidity });
  const newComp = new componentModel(val);
  await newComp.save();
  res.json({ message: "successfully added" });
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});




