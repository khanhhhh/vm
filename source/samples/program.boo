structure of a typical program
list of variable declaration.

//class
var foo: type = tuple[x: typex, y: typey];

//trait
var footrait: trait[foo] = {
    fooconstructor,
    var destructor: function = (self: foo) {
        delete...
    }
}
var fooconstructor: function = (self: foo, value1: typex, value2: typey) {
    self.x = typex;
    self.y = typey;
}


//function
var func1: function = (param1) -> (return1) {
    // implementation
};
//generics
var func2: function = (function f1, type t1, int value) -> (int) {
    //implemtnation
}
//main function
var main: function =  (param main) -> (param main) {
    // implementation
}