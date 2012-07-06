var str = ".";
for( var i = 1; i < 200000; i ++ ){
    str += "" + i + "";
}

var product = 1;
for( var i = 0; i < 7; i++){
    product *= parseInt(str.substr(Math.pow(10,i),1));
}
console.log(product);
