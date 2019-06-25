var fib: addr = (x: int) -> int {
    var base: addr = 0x1;
    0x0 <- 1;
    0x1 <- 1;
    while (base < x) {
        base = base + 1;
        base <- deref(base[-1]) + deref(base[-2]);
    }
    return deref(base);
}
var main: addr = () -> int {
    var x: int = 28;
    var data: addr = 0x0;
    data[0] <- fib(x);
    return 0;
}