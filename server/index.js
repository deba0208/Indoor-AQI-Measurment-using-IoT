// server.js
const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const fs = require("fs");
const mongoose = require("mongoose")
const { title } = require("process");
const app = express();
const PORT = 3000;

app.use(express.json());
app.use(cors());

const authentication = (req, res, next) => {
  let auHeader = req.headers.split(" ")[1];
  if (auHeader === "123456789") {
    next();
  } else {
    res.json({ message: "authentication failed" });
  }
}

app.get("/data", (req, res) => {
  fs.readFile("data.json", "utf-8", (err, data) => {
    if (err) throw err;
    res.json(JSON.parse(data));
  });
});
app.post("/data", authentication, (req, res) => {
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
      res.send(creatNewEntry);
    });
  });
  // Process the data as needed
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
