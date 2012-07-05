function permute (v, m){
    for(var p = -1, j, k, f, r, l = v.length, q = 1, i = l + 1; --i; q *= i);
    for(x = [new Array(l), new Array(l), new Array(l), new Array(l)], j = q, k = l + 1, i = -1;
        ++i < l; x[2][i] = i, x[1][i] = x[0][i] = j /= --k);
    for(r = new Array(q); ++p < q;)
        for(r[p] = new Array(l), i = -1; ++i < l; !--x[1][i] && (x[1][i] = x[0][i],
            x[2][i] = (x[2][i] + 1) % l), r[p][i] = m ? x[3][i] : v[x[3][i]])
            for(x[3][i] = x[2][i], f = 0; !f; f = !f)
                for(j = i; j; x[3][--j] == x[2][i] && (x[3][i] = x[2][i] = (x[2][i] + 1) % l, f = 1));
    return r;
};

var Store = {
    vals: {3: {},4: {},5: {},6: {},7: {},8: {}},
    ary: { 3: [],4: [],5: [],6: [],7: [],8: []},
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
                if(v>=10){
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

for ( var i = 1; i < 1000; i++){
    if(Store.store(i) > 10000){
        break;
    }
}

var sequences = permute([3,4,5,6,7]);
for( var k in Store.vals[8] ){
    for( var v in Store.vals[8][k] ){
        for ( var i = 0; i < sequences.length; i++){
            var cycle = [Store.vals[8][k][v]];
            var scopy = sequences[i].slice(0);
            scopy.push(8);
            findSequence(Store.vals,scopy,cycle,v);
            if(cycle.pop() == cycle[0]){
                console.log(cycle);
                var sum = 0;
                for ( var j = 0; j < cycle.length; j ++){
                    sum += cycle[j];
                }
                console.log(sum);
                process.exit();
            }
        }
    }
}


function findSequence(vals,polygons,sequence,previous){
    var p = polygons.shift();
    if(p){ 
        if(Store.vals[p].hasOwnProperty(previous)){
            for(var kv in Store.vals[p][previous]){
                if(Store.vals[p][previous].hasOwnProperty(kv)){
                    sequence.push(Store.vals[p][previous][kv]);
                    findSequence(vals,polygons,sequence,kv);
                }
            }
        }
    }
}
