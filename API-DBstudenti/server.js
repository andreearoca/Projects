const http = require('http');
const mongodb = require('mongodb');
const {MongoClient, ObjectId} = require("mongodb");
const {getPostData} = require("./utils");

let db;


const server = http.createServer(async (req, res) => {
    if (req.url === '/api/students' && req.method === 'GET') {

        const students = await db.collection("students").find({}).toArray();
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify(students));
    }
    else if (req.url.match(/\/api\/students\/([0-9]+)/) && req.method === 'GET') {
        const id = req.url.split('/')[3];
        try {
            const student = await db.collection("students").find({ _id: new ObjectId(id) }).toArray();

            if(student.length === 0){
                res.writeHead(404, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify({ message: 'Student not found'}));
            }
            else {
                res.writeHead(200, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify(student));

            }
        } catch (error) {
            console.log(error);
        }
    }
    else if (req.url === '/api/students' && req.method === 'POST') {
        try {
            const body = await getPostData(req);

            await db.collection("students").insertMany( JSON.parse(body) );


            res.writeHead(201, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify(JSON.parse(body)));
        } catch (error) {
            console.log(error);
        }
    }
    else if (req.url.match(/\/api\/students\/([0-9]+)/) && req.method === 'POST') {
        try {
            const id = req.url.split('/')[3];
            const studentId = await db.collection("students").find({ _id: new ObjectId(id) }).toArray();

            if(studentId.length === 0){
                const body = await getPostData(req);

                const { name, course, grade } = JSON.parse(body);

                const student = {
                    _id: new ObjectId(id),
                    name,
                    course,
                    grade
                };

                await db.collection("students").insertOne( student );


                res.writeHead(201, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify(student));
            } else {
                res.writeHead(404, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify({message: `Student with id ${id} already exists!`} ));
            }
        } catch (error) {
            console.log(error);
        }
    }
    else if(req.url.match(/\/api\/students\/([0-9]+)/) && req.method === 'PUT') {
        const id = req.url.split('/')[3];
        try {
            const student = await db.collection("students").find({ _id: new ObjectId(id) }).toArray();

            if(student.length === 0) {
                res.writeHead(404, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify({ message: 'Student not found'}));
            } else {

                const body = await getPostData(req);

                const { name, course, grade } = JSON.parse(body);

                const updatedStudent = await db.collection("students").updateOne(
                    { _id: new ObjectId(id) },
                    { $set: { name:name, course:course, grade:grade } });

                const studentAfterUpdate = await db.collection("students").find({ _id: new ObjectId(id) }).toArray();

                res.writeHead(200, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify(studentAfterUpdate));
            }
        } catch (error) {
            console.log(error);
        }
    }
    else if(req.url === '/api/students' && req.method === 'PUT') {
        try {
            const body = await getPostData(req);

            const { name, course, grade } = JSON.parse(body);

            const updatedStudents = await db.collection("students").updateMany(
                { },
                { $set: { name:name, course:course, grade:grade } });

            const studentsAfterUpdate = await db.collection("students").find({ }).toArray();

            res.writeHead(200, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify(studentsAfterUpdate));

        } catch (error) {
            console.log(error);
        }
    }
    else if(req.url.match(/\/api\/students\/([0-9]+)/) && req.method === 'DELETE') {
        const id = req.url.split('/')[3];
        try {
            const student = await db.collection("students").find({ _id: new ObjectId(id) });

            if(student.length === 0){
                res.writeHead(404, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify({ message: 'Student not found'}));
            }
            else {
                await db.collection("students").deleteOne({ "_id": new ObjectId(id) });


                res.writeHead(200, { 'Content-Type': 'application/json' });
                res.end(JSON.stringify({message: `Student ${id} removed`}));
            }
        } catch (error) {
            console.log(error);
        }
    }
    else if(req.url === '/api/students' && req.method === 'DELETE') {
        try {
            await db.collection("students").deleteMany({ });


            res.writeHead(200, { 'Content-Type': 'application/json' });
            res.end(JSON.stringify({message: `All students removed`}));

        } catch (error) {
            console.log(error);
        }
    }
    else {
        res.writeHead(404, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify({ message: 'Route Not Found' }));
    }
})

async function main(){
    const uri = "mongodb+srv://--confidential_data--";
    const client = new MongoClient(uri);

    try {
        await client.connect();
        db = await client.db("Node-API");
        console.log(`${db.databaseName}`);

    } catch (e){
        console.error(e);
    }

}
main().catch(console.error);

const PORT = process.env.PORT || 5000;

server.listen(PORT, () => console.log(`Server running on port ${PORT}`));