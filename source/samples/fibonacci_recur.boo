var fib : addr = (x: int) -> int {
    if (x <= 2) {
        return 1;
    } else {
        return fib(x-1) + fib(x-2);
    }
}
var main: addr = () -> int {
    var x: int = 28;
    var data: addr = 0x0;
    data[0] <- fib(x);
    return 0;
}
