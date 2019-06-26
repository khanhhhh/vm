structure of a typical program
list of variable declaration.

//class
var foo: type = tuple[x: typex, y: typey];

//trait
var footrait: trait[foo] = {
    // first function must be destructor
    // object has it own life time, destructor is called when object is destroyed
    var destructor: function = (self: foo) {
        delete...
    },
    fooconstructor
}
var fooconstructor: function = (value1: typex, value2: typey) -> foo {
    var self: foo = 0;
    self.x = typex;
    self.y = typey;
    return self;
}
var fooinstance: foo = footrait.fooconstructor(1, 2);

//function
var func1: function = (param1) -> (return1) {
    // implementation
};
//generics
var func2: function = (f1: function f1, t1: type, value: int) -> (int) {
    //implemtnation
}
//main function
var main: function =  (param main) -> (param main) {
    // implementation
    var a = array[int, 3] = (1, 2, 3);
    //fucntion call
    func1(param1);
    //array indexing
    a(1);
    return 0;
}