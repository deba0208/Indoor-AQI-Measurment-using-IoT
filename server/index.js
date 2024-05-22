// server.js
//EyVc7dHpN9gtrzxa
//mongodb+srv://dasbabai2017:<password>@allcomponantvalue.226u6wj.mongodb.net/
const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const fs = require("fs");
const mongoose = require("mongoose")
const { title } = require("process");
const cors = require("cors");
const mongoose = require("mongoose");
const { componentModel } = require("./Model/Mongo_model");
const app = express();
app.use(cors());
app.use(express.json());
const PORT = 3000;

app.use(bodyParser.json());
app.get("/data", (req, res) => {
  fs.readFile("data.json", "utf-8", (err, data) => {
    if (err) throw err;
    res.json(JSON.parse(data));
  });
});
app.post("/data", (req, res) => {
  const creatNewEntry = {
    id: Math.floor(Math.random() * 1000000),
    date: req.body.dateTime,
  };
  fs.readFile("data.json", "utf-8", (err, data) => {
    if (err) throw err;
    const entry = JSON.parse(data);
    entry.push(creatNewEntry);
    fs.writeFile("data.json", JSON.stringify(entry), (err) => {
      if (err) throw err;
      res.status(201).send(creatNewEntry);
    });
  });
  // Process the data as needed
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});




