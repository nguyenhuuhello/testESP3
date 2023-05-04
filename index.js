const express = require('express')
const app = express()

const  mongoose = require ("mongoose"); //hỗ trợ kết nối DB
// const dataSchema = require('./models/DataSchema');
// const Data = require('./config/db')
//kết nối mongoDB
// Data.connect();

//Dùng http để tạo http server
const http = require('http')
const server = http.createServer(app)

//Sử dụng socket.io
const{Server} = require('socket.io')
const io = new Server(server)

//tạo đường dẫn web trả về
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/index.html');
})


//kết nối với mongoDB
// mongoose.connect('mongodb://127.0.0.1:27017/esp32_data', 
//     { useNewUrlParser: true, useUnifiedTopology: true })
//     .then(() => console.log('MongoDB connected...'))
//     .catch(err => console.log(err));



//Tạo kết nối
io.on('connection', (socket) => {
    console.log('Client connected');

    // dataSchema.find().then(result => {
    //     socket.emit('on-btn', result)
    // })

    socket.on('on-chat', message => {
        console.log(message)
        //gửi tới toàn bộ client
        io.emit('user-chat', message)
    });

    socket.on('event', message => {
        console.log(1);
        //gửi tới toàn bộ client
        io.emit('event', message)
    });

    

    socket.on('status', message => {
        console.log(message)
        //gửi tới toàn bộ client
    });

    socket.on('on-btn', led => {
        console.log(led);

        io.emit('on-btn', led)

        //save to DB
        // const msg = new dataSchema({ led });
        // msg.save().then(() => {
        //     //Gửi cho toàn bộ client
        //     io.emit('on-btn', led)
        // })
    });

    //{led: true} là điều kiện tìm kiếm và data là kết quả 
    //trả về là một mảng các document thoả mãn điều kiện tìm kiếm


    // dataSchema.find({ led: true })
    //     .sort({ createdAt: -1 }) // sắp xếp theo thời gian giảm dần
    //     .limit(1) // chỉ lấy 1 document đầu tiên trong kết quả trả về
    //     .then((data) => {
    //         message = data[0].led;
    //         console.log('Value from DB', message);

    //         //cập nhật tới client
    //         io.emit('on-btn', message)
    //     }).catch((err) => {
    //         console.log(err);
    //      });



    // socket.on('checkbox_change', (isChecked) => {
    //     console.log(isChecked)
    //     io.emit('checkbox_change', isChecked);
    //   });

    // socket.on('sensorData', (data) => {
    //     console.log('Received sensor data:', data);
    //     // Xử lý dữ liệu nhận được ở đây
    //   });

    // socket.on('on-btn', (data) => {
    //     const input = new Data({ led: data.led});
    //     // input.save((err) => {
    //     //   if (err) return console.error(err);
    //     //   console.log('Message saved to MongoDB');
    //     // })

    //     input.save()
    //         .then(() => {
    //             console.log('Message saved to MongoDB');
    //         })
    //         .catch((err) => {
    //             console.error(err);
    //         });
    //     });

})

server.listen(3000, () => {
    console.log('Listenning on port 3000')
})