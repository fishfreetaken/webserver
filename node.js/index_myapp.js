var express = require('express');
var router = express.Router();

var app = express();

var mysql=require('mysql');
var pool=mysql.createPool({
  connectionLimit : 30,
  host            : 'localhost',
  user            : 'root',
  password        : '20170622',
  database        : 'face_db' //foot_db
});
const crypto = require('crypto');

//面向用户，另一个面向管理

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.get('/cf/:name',function(req,res,next){
  console.log(req.params.name);
  //res.redirect('../userdata');
  //var name='ernrtnrhrtjyz';
  ///res.redirect('../hongse.html?user='+name);
  if(req.params.name.length!=64){
    //console.log('myte');
    var err = new Error('Not 1 Found');
    err.status=404;
    res.locals.message = err.message;
    res.locals.error = req.app.get('env') === 'development' ? err : {};
    res.status(404);
    res.render('error');
    return ;
  }
 //console.log('myteahrh');
  pool.getConnection(function(err, connection) {
    // Use the connection
    connection.query('SELECT ider from users where hashsec=? ',req.params.name, function (error, results, fields) {
      // And done with the connection.
      connection.release();
      if(results.length==1){
        res.redirect('../objtest.html?user='+req.params.name);
      }else{
        var err = new Error('Not 2 Found');
        err.status=404;
        res.locals.message = err.message;
        res.locals.error = req.app.get('env') === 'development' ? err : {};
        res.status(404);
        res.render('error');
      }
      // Handle error after the release.
      if (error) throw error;
      // Don't use the connection here, it has been returned to the pool.
    });
  });
});

router.get('/userdata',function(req,res,next){ //下行查阅
 // console.log(req.query.user);
  
  if(req.query.user.length!=64){ //到最后还是要加上去的！
    //res.send('errostr');
    console.log('re achieve!');
    res.send('not enough len!');
    return ;
  }
  pool.getConnection(function(err, connection) {
    // Use the connection
      connection.query('SELECT telephone,username,sex,length_l ,width_l ,ballgirth_l ,medragirth_l ,rakegirth_l,firsttoe_l ,secondtoe_l , thirdtoe_l, firstphalangea_l, firstphalangeb_l ,length_r,width_r ,ballgirth_r ,medragirth_r ,rakegirth_r ,firsttoe_r ,secondtoe_r, thirdtoe_r, firstphalangea_r , firstphalangeb_r from users where hashsec=? ',req.query.user, function (error, results, fields) {
        // And done with the connection.
        connection.release();
        //console.log(results);
        if(results.length){
          res.send(results[0]);
        }else{
          res.send('errorstr');
        }
        // Handle error after the release.
        if (error) throw error;
        // Don't use the connection here, it has been returned to the pool.
      });
    });
});

router.get('/login', function (req, res) {
  //var html = "<h2>你好, " + req.query.username + "</h2><a href='/logout'>退出</a>";
  //res.send(html);
  res.send({af:'grq',wg:'gqeh',tn:1256});
});

router.get('/loadfile',function(req,res,next){
   //res.sendFile(process.cwd() +'/public/excel/123.xlsx');
   res.redirect('http://localhost:3000/excel/123.xlsx'); //这种方式可能会好一点，可以使用nginx静态文件代理；
});


router.get('/faceuserinqury',function(req,res,next){
    //console.log(req.user);
    //res.send('iam socke!');
    if(req.query.id.length!=64){ //到最后还是要加上去的！
      //res.send('errostr');
      console.log('re achieve!');
      res.send('error 1!');//not need length!
      return ;
    }
    pool.getConnection(function(err, connection) {
      // Use the connection
        connection.query('SELECT * from faceusers where hashsec=? ',req.query.id, function (error, results, fields) {
          // And done with the connection.
          connection.release();
          //console.log(results);
          if(results.length){
            res.send(results[0]);
          }else{
            res.send('errorstr');
          }
          // Handle error after the release.
          if (error) throw error;
          // Don't use the connection here, it has been returned to the pool.
        });
      });
});

router.get('/faceuserinqury2',function(req,res,next){
  pool.getConnection(function(err, connection) {
    // Use the connection
      connection.query('SELECT * from faceusers where ider=5 ', function (error, results, fields) {
        // And done with the connection.
        connection.release();
        //console.log(results);
        if(results.length){
          res.send(results[0]);
        }else{
          res.send('errorstr');
        }
        // Handle error after the release.
        if (error) throw error;
        // Don't use the connection here, it has been returned to the pool.
      });
    });

});


module.exports = router;
