var Store = {
    vals: {
        3: {},4: {},5: {},6: {},7: {},8: {}
    },
    ary: {
        3: [],4: [],5: [],6: [],7: [],8: []
    },
    nFuncts: {
        3: function(n){ return (n * (n+1))/2 },
        4: function (n) { return n * n },
        5: function (n) { return (n * (3*n-1))/2 },
        6: function (n) { return n * (2*n-1) },
        7: function (n) { return n * (5*n-3)/2 },
        8: function (n) { return n * (3*n-2) }
    },
    store: function(n){
        var value;
        for(var i = 3; i <= 8; i++){
            value = this.nFuncts[i](n);
            this.ary[i].push(value);
            if(value>1000 && value < 10000){
                k = Math.floor(value/100);
                v = value%100;
                if(v>10){
                    if(!this.vals[i].hasOwnProperty(k)){
                        this.vals[i][k] = {};
                    }
                    this.vals[i][k][v] = value;
                }
            }
        }
        return this.nFuncts[3](n);
    }
};

for ( var i = 1; i < 3000; i++){
    if(Store.store(i) > 10000){
        break;
    }
}
console.log(Store.vals);
//console.log(Store.ary);

for ( var k8 in Store.vals[8] ){
    for( var k3 in Store.vals[8][k8] ){
        if( Store.vals[3].hasOwnProperty(k3)){
            for( var k4 in Store.vals[3][k3] ){
                console.log("3:"+k3+k4);
                if( Store.vals[4].hasOwnProperty(k4)){
                    for( var k5 in Store.vals[4][k4] ){
                        console.log("4:"+k4+k5);
                        if( Store.vals[5].hasOwnProperty(k5)){
                            for( var k6 in Store.vals[5][k5] ){
                                console.log("5:"+k5+k6);
                                if( Store.vals[6].hasOwnProperty(k6)){
                                    for( var k7 in Store.vals[6][k6] ){
                                        console.log("6:"+k6+k7);
                                        if( Store.vals[7].hasOwnProperty(k7)){
                                            for( var k8 in Store.vals[7][k7] ){
                                                console.log("\n\n7:"+k7+k8);
                                                if( Store.vals[8].hasOwnProperty(k8)){
                                                    console.log(
                                                        k3+""+k4+","+
                                                        k4+""+k5+","+
                                                        k5+""+k6+","+
                                                        k6+""+k7+","+
                                                        k7+""+k8+","+
                                                        k8+""+k3+"\n");
                                                    sum = parseInt(k3)+parseInt(k4)+parseInt(k5)+parseInt(k6)+parseInt(k7)+parseInt(k8);
                                                    sum = sum * 101;
                                                    console.log(sum);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
