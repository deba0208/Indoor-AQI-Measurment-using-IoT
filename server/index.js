// server.js
const express = require("express");
const bodyParser = require("body-parser");
const fs = require("fs");
const { title } = require("process");
const app = express();
const PORT = 3000;

app.use(bodyParser.json());
app.get("/data", (req, res) => {
  fs.readFile("data.json", "utf-8", (err, data) => {
    if (err) throw err;
    res.status(200).json(JSON.parse(data));
  });
});
app.post("/data", (req, res) => {
  {
    const creatNewEntry = {
      id: Math.floor(Math.random() * 1000000),
      date: req.body,
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
  } // else {
  //   res.send("Error");
  // }
  // Process the data as needed
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
