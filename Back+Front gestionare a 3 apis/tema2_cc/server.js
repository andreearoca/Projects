const express = require('express');
const app = express();
const bodyParser = require('body-parser');
const axios = require("axios");
const cors = require('cors');
const config = require('config')

app.use(cors());

jsonParser = bodyParser.json();

const PORT = 3001;

app.listen(PORT, () => {
    console.log(`Server started on port ${PORT}`);
});

app.get('/hello', (req, res) => {
    res.send('Hello, world!');
});

app.post('/translate', jsonParser, (req, res) => {
    const encodedParams = new URLSearchParams();
    encodedParams.append("q", req.body.q);
    encodedParams.append("target", req.body.target);
    encodedParams.append("source", req.body.source);
    const options = {
        method: req.method,
        url: 'https://google-translate1.p.rapidapi.com/language/translate/v2',
        headers: {
            'content-type': 'application/x-www-form-urlencoded',
            'Accept-Encoding': 'application/gzip',
            'X-RapidAPI-Key': config.get("api.key"),
            'X-RapidAPI-Host': 'google-translate1.p.rapidapi.com'
        },
        data: encodedParams
    }
    axios.request(options).then(function (response) {
        console.log(JSON.stringify(response.data));
        res.send(JSON.stringify({"status": 200, "error": null, "response": JSON.stringify(response.data)}));
    }).catch(function (error) {
        console.error(error);
        res.send(JSON.stringify({"status": 404, "error": null, "response": 'api error'}));
    });
});

app.get('/getStudents', jsonParser, (req, res) => {
    axios.get('http://localhost:5000/api/students')
        .then(function (response) {
           // console.log(JSON.stringify(response.data));
            res.send(JSON.stringify({"status": 200, "error": null, "response": response.data}))
    }).catch(function (error) {
        console.error(error);
        res.send(JSON.stringify({"status": 404, "error": null, "response": 'api error'}));
    });
});

app.post('/addStudent', jsonParser, (req, res) => {
    console.log(JSON.stringify(req.body))
    const options = {
        method: 'POST',
        url: 'http://localhost:5000/api/students',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(req.body)
    }
    axios.request(options)
        .then(function (response) {
            console.log(JSON.stringify(response.data));
            res.send(JSON.stringify({"status": 200, "error": null, "response": response.data}))
        }).catch(function (error) {
        console.error(error);
        res.send(JSON.stringify({"status": 404, "error": null, "response": 'api error'}));
    });
});

app.post('/weather', jsonParser, (req, res) => {
    console.log(JSON.stringify(req.body.q))

    const options = {
        method: 'GET',
        url: 'https://weatherapi-com.p.rapidapi.com/current.json',
        params: {q: JSON.stringify(req.body.q)},
        headers: {
            'X-RapidAPI-Key': config.get("api.key"),
            'X-RapidAPI-Host': 'weatherapi-com.p.rapidapi.com'
        }
    }
    axios.request(options).then(function (response) {
        console.log(JSON.stringify(response.data));
        res.send(JSON.stringify({"status": 200, "error": null, "response": JSON.stringify(response.data)}));
    }).catch(function (error) {
        console.error(error);
        res.send(JSON.stringify({"status": 404, "error": null, "response": 'api error'}));
    });
});