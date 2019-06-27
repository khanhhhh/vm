structure of a typical program
list of variable declaration.

//class/tuple has its 
var foo: type = tuple[x: typex, y: typey];

//trait
var footrait: trait[foo] = {
    // first function must be destructor
    // object has it own life time, destructor is called when object is destroyed
    var destructor: function = tuple[self: foo] -> int {
        delete...
    },
    fooconstructor
}
var fooconstructor: function = tuple[value1: typex, value2: typey] -> foo {
    var self: foo = 0;
    self.x = typex;
    self.y = typey;
    return self;
}
var fooinstance: foo = footrait.fooconstructor(1, 2);

//function param can be any type, typically tuple
var func1: function = typein1 -> typeout1 {
    // implementation
};
//generics
var func2: function = tuple[f1: function f1, t1: type, value: int] -> int {
    //implemtnation
}

// block of code takes result from last expression
{
    1;
    2,
    var a: int = 3
}
//main function
var main: function =  int -> int {
    // 2 implementations of array: tuplevalue = (x, y, z) or (x; y; z)
    var a = array[int, 3] = (1, 2, 3);
    var b = tuple[v1: int, v2: int, v3: int] = (1, 2, 3);
    //fucntion call: funcname tuplevalue (tuplevalue is define as list a expressions enclosed with parentheses)
    func1 (1, 2, 3);
    //array indexing: similar to function
    a (1);
    return 0;
}