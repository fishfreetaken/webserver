var express = require('express');
var router = express.Router();

var excel=require('exceljs');

var mysql=require('mysql');

var iconv = require('iconv-lite');

//var QRCode = require('qrcode');

var pool=mysql.createPool({
  connectionLimit : 100,
  host            : 'localhost',   
  user            : 'root',
  password        : '20170622',
  database        : 'face_db'//foot_db
});
const crypto = require('crypto');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.get('/userinfo',function(req,res,next){ //这个是,脚型的上传存储

  var cc=0;
  for(var i in req.query){
    cc++;
  }
  if((cc<64)||(req.query.phone==undefined)){
    res.redirect('/');
  }
  var inserts={
    telephone:req.query.phone,
    username:req.query.name,
    //objlocation:'model/obj/node-'+req.query.file,
    sex:req.query.sex, //new add!
    length_l:req.query.q1,
    width_l:req.query.q2,
    ballgirth_l:req.query.q3,
    medragirth_l:req.query.q4,
    rakegirth_l:req.query.q5,
    firsttoe_l:req.query.q6,
    secondtoe_l:req.query.q7,
    thirdtoe_l:req.query.q8,
    firstphalangea_l:req.query.q9,
    firstphalangeb_l:req.query.q10,

    length_r:req.query.q11,
    width_r:req.query.q12,
    ballgirth_r:req.query.q13,
    medragirth_r:req.query.q14,
    rakegirth_r:req.query.q15,
    firsttoe_r:req.query.q16,
    secondtoe_r:req.query.q17,
    thirdtoe_r:req.query.q18,
    firstphalangea_r:req.query.q19,
    firstphalangeb_r:req.query.q20,

  };

  pool.getConnection(function(err, connection) {
    // Use the connection
    connection.query('INSERT into users SET ider=null, timereg=now(), ?',inserts, function (error, results, fields) {
      // And done with the connection.
      if (error) throw error;
      connection.release();
      //console.log('update id:'+results.insertId);
      var sg=results.insertId;
      var hash = crypto.createHash('sha256');
      hash.update(sg.toString());
      
      var mhash=hash.digest('hex');

      pool.getConnection(function(err, connection) {
        connection.query('update users set hashsec =? where ider=?',[mhash,parseInt(sg)], function (error, results, fields) {
          connection.release();
          if (error) throw error;
        });
      });
      //var link="http://192.168.0.112:3000/objtest.html?user="+mhash;
      //var link="http://17347b39l4.imwork.net:13570/objtest2.html?user="+mhash;
      res.send(mhash);
    });
  });
});

function isLoggedIn(req, res, next) {
  //console.log('is logged in!');
    if (req.isAuthenticated())
        return next();

    res.send('You have no authority!');
}

router.get('/excel',isLoggedIn,function(req,res,next){ //登录成功的服务
  pool.getConnection(function(err, connection) {
       connection.query('select username,sex,telephone,length_l,width_l ,ballgirth_l ,medragirth_l ,rakegirth_l ,firsttoe_l ,secondtoe_l , thirdtoe_l, firstphalangea_l, firstphalangeb_l ,length_r,width_r ,ballgirth_r,medragirth_r ,rakegirth_r ,firsttoe_r,secondtoe_r, thirdtoe_r, firstphalangea_r, firstphalangeb_r from users', function (error, results, fields) {
          if(error) throw error;
          connection.release();
          //console.log(results[1]);
          var o=[];

          for(var i=0;i<results.length;i++){
            var s=[];
            for(var j in results[i]){
              if(j=='sex'){
                if(results[i][j]){
                  s.push('男');
                }else{
                  s.push('女');
                }
                continue;
              }
              s.push(results[i][j].toString());
            }
            o.push(s);
          }
          createExcel(o,res);
      });
  });
});

var seqnum=0;

router.get('/faceinfo',function(req,res,next){ //这个面部参数是上传存储
  //res.send('hello winhttp!');
  
  console.log(req.query);
  var inserts={
    name:req.query.name,
    telephone:req.query.phone,
    sex:req.query.sex, //new add!

    objlocation:req.query.location,

    eyelen:req.query.eyelen,
    widest:req.query.widest,
    eartoeye:req.query.earlen,
    angle:req.query.angle
  }
  
  pool.getConnection(function(err, connection) {
    // Use the connection

    connection.query('INSERT into users SET ider=null, timereg=now(), ?',inserts, function (error, results, fields) {
      // And done with the connection.
      if (error) throw error;
      connection.release();
     // seqnum +=1;

      var sg=results.insertId;
      var hash = crypto.createHash('sha256');
      hash.update(sg.toString());
      
      var mhash=hash.digest('hex');

      pool.getConnection(function(err, connection) {
        connection.query('update users set hashsec =? where ider=?',[mhash,parseInt(sg)], function (error, results, fields) {
          connection.release();
          if (error) throw error;
        });
      });
      res.send(mhash);
    });
  });
});
//var globnum=0;

router.get('/faceinfoline',function(req,res,next){
     ///console.log(req.query);
     //res.send('grereebjdyytjtetn');
     pool.getConnection(function(err, connection) {
        // Use the connection
    
        connection.query('INSERT into faceusers SET ider=null, timereg=now(), ?',req.query, function (error, results, fields) {
          // And done with the connection.
          if (error) throw error;
          connection.release();
         // seqnum +=1;
    
          var sg=results.insertId;
          var hash = crypto.createHash('sha256');
          hash.update(sg.toString());
          
          var mhash=hash.digest('hex');

          res.send(mhash);
          console.log('sg: '+sg);
    
          pool.getConnection(function(err, connection) {
            connection.query('update faceusers set hashsec =? where ider=?',[mhash,parseInt(sg)], function (error, results, fields) {
              connection.release();
              console.log('update!');
              if (error) throw error;
            });
          });
          //res.charset = 'utf-8';

          console.log('resend: '+mhash);
        });
      });
});

router.get('/faceperson',function(req,res,next){
  console.log(req.query);
  //res.send('grereebjdyytjtetn');
  pool.getConnection(function(err, connection) {
     // Use the connection
     connection.query('INSERT into faceusers SET ider=null, timereg=now(), ?',req.query, function (error, results, fields) {
       // And done with the connection.
       if (error) throw error;
       connection.release();
      // seqnum +=1;
 
       var sg=results.insertId;
       var hash = crypto.createHash('sha256');
       hash.update(sg.toString());
       
       var mhash=hash.digest('hex');

       res.send(results.insertId.toString());
       
       //console.log('sg: '+sg);
 
       pool.getConnection(function(err, connection) {
         connection.query('update faceusers set hashsec =? where ider=?',[mhash,results.insertId], function (error, results, fields) {
           connection.release();
           console.log('update!');
           if (error) throw error;
         });
       });
       //res.charset = 'utf-8';
     });
   });
});


router.get('/faceparam',function(req,res,next){
///console.log(req.query);
 ///res.charset = 'utf-8';
  var idt=parseInt(req.query.ider);
 // console.log('idt:'+idt);
  delete req.query.ider;
  //res.send('gewwgwragbre');
  pool.getConnection(function(err, connection) {
    connection.query('SELECT hashsec from faceusers where ider=?',idt, function (error, results, fields) {
      connection.release();
      if (error) throw error;
      //console.log('results:');
     // console.log(results);
      // if(results[0].hashsec!="undefined"){
        res.send(results[0].hashsec);//吃大亏了[0]
      // }else{
      //   res.send('no hashsec');
      // }
      
    });
  });
  pool.getConnection(function(err, connection) {
    connection.query('update faceusers SET ? where ider=?',[req.query,idt], function (error, results, fields) {
      connection.release();
      if (error) throw error;
      console.log('para update');
    });
  });

});

router.get('/facepost',function(req,res,next){ //这个是上传存储//for test

  console.log(req.query);
  var tt= new Buffer(req.query.name);
  console.log(tt.toString('utf8'));
  var str=iconv.decode(tt,'GB2312');
  console.log(str);

  res.send('hello winhttp this is post!');
  
  //console.log(req.body);
});

module.exports = router;

function createExcel(inputdata,res){
    var workbook=new excel.Workbook();
    var worksheet=workbook.addWorksheet('sheet1');

     worksheet.getColumn(3).width=13;

     worksheet.getColumn(9).width=12;
     worksheet.getColumn(10).width=12;
     worksheet.getColumn(11).width=12;
     worksheet.getColumn(12).width=14;
     worksheet.getColumn(13).width=14;

     worksheet.getColumn(19).width=12;
     worksheet.getColumn(20).width=12;
     worksheet.getColumn(21).width=12;
     worksheet.getColumn(22).width=14;
     worksheet.getColumn(23).width=14;

    var ficell=worksheet.getCell('A1');
    ficell.font={
        family: 4,
        size: 16,
        bold: true
    }
    ficell.value = '（深度创新科技）客户脚型资料 （单位：毫米）  '+new Date().toLocaleString();;
    ficell.alignment = { vertical: 'middle', horizontal: 'center' };
    worksheet.mergeCells('A1:W2');

    var firstrow = ['姓名','性别','电话','左脚长','左脚宽','左掌围','左腰围','左背围','左第一趾围','左第二趾围','左第三趾围','左第一趾骨长A','左第一趾骨长B','右脚长','右脚宽','右掌围','右腰围','右背围','右第一趾围','右第二趾围','右第三趾围','右第一趾骨长A','右第一趾骨长B'];
    worksheet.addRow(firstrow);

    for(var j=0;j<inputdata.length;j++){
      worksheet.addRow(inputdata[j]);
    }

    workbook.xlsx.writeFile('C:/Users/47108/Desktop/nginx-1.12.1/images/excel/123.xlsx').then(function(){
      res.redirect('/excel/123.xlsx');
      //console.log("xlsx write done");
    });
}