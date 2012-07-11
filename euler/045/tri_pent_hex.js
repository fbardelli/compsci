var Store = {
    vals: {"tri": {},"pent": {},"hex": {}},
    nFuncts: {
        "tri": function(n){ return (n * (n+1))/2 },
        "pent": function (n) { return (n * (3*n-1))/2 },
        "hex": function (n) { return n * (2*n-1) },
    },
    store: function(n){
        var value;
        var funcs = ["hex","pent","tri"];
        var last = 0;
        for(var i = 0; i < funcs.length; i++){
            var f = funcs[i];
            value = this.nFuncts[f](n);
            this.vals[f][value] = n;
            last = value;
        }
        if(this.vals["hex"].hasOwnProperty(last) 
            && this.vals["pent"].hasOwnProperty(last) ){
            return last;
        }
    }
};

solutions = [];
i=0;
while (solutions.length < 3){
    if(a = Store.store(i++)){
        solutions.push(a);
    }
}

console.log(solutions.pop());
