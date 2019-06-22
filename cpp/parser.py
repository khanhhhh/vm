#!/usr/bin/env python3
code2name = {
        0x00 : "halt",
	0x01 : "nop",
	# 0x1.. : LOAD STORE
	0x11 : "load_code",
	0x12 : "load_code_array",
	0x13 : "load_data",
	0x14 : "load_data_array",
	0x15 : "load_stack",
	0x16 : "load_stack_array",
	0x17 : "store_data",
	0x18 : "store_data_array",
	0x19 : "store_stack",
	0x1a : "store_stack_array",
	# 0x02.. : STACK MANIPULATION
	0x20 : "push",
	0x21 : "push_array",
	0x22 : "pop",
	0x23 : "pop_array",
	0x24 : "dup",
	0x25 : "dup_array",
	0x26 : "swap",
	0x27 : "swap_array",
	# 0x3.. : ARITHMETIC
	0x30 : "iadd",
	0x31 : "fadd",
	0x32 : "isub",
	0x33 : "fsub",
	0x34 : "imul",
	0x35 : "fmul",
	0x36 : "idiv",
	0x37 : "fdiv",
	0x38 : "irem",
	0x39 : "ineg",
	0x3a : "fneg",
	# 0x4.. : TYPE CONVERSION
	0x40 : "i2f",
	0x41 : "f2i",
	# 0x5.. : JUMP
	0x50 : "jump",     
	0x51 : "ifeq_jump",
	0x52 : "iflt_jump",
	0x53 : "ifgt_jump",
	0x54 : "ifle_jump",
	0x55 : "ifge_jump",
	0x56 : "ifne_jump",
	# 0x6.. : FUNCTION CALL
	0x60 : "push_fp",
	0x61 : "call_fp",
	0x62 : "return0",
	0x63 : "return1",
	0x64 : "return1_array",
	# 0xf.. : PRINT
	0xf0 : "print_int",
	0xf1 : "print_float",
	0xf2 : "print_char",
}
name2code = dict((value, key) for (key, value) in code2name.items())

import pdb
import re
class instruction:
    def __init__(self, name, opname, param, line):
        self.name = name
        self.opname = opname
        self.param = param
        self.line = line
    def __str__(self):
        return "{{name: \"{}\", opname: \"{}\", param: {}, line = {}}}".format(
                self.name,
                self.opname,
                self.param,
                self.line)
    def __repr__(self):
        return self.__str__()

def parse(filename):
    # read file
    lines = []
    with open(filename) as f:
        for l in f:
            lines.append(l)

    inslist = []
    linenum = 0;
    for ins in lines:
        linenum += 1
        # remove white space and strip
        ins = re.sub("\s+", " ", ins).strip()
        # get name and code
        name = ""
        code = ""
        ins = ins.split(":")
        if (len(ins) > 1): # has name
            name = ins[0]
            code = ins[1]
        else:
            code = ins[0]
        name = name.strip()
        code = code.strip()

        # get opname and param
        code = code.split(" ")
        opname = ""
        param = ""
        if (len(code) > 1): # has param
            opname = code[0]
            param = code[1]
        else:
            opname = code[0]
        # split param
        param = param.strip().split(" ")

        if (opname == ""): continue
        inslist.append(
            instruction(name, opname, param, linenum)
        )
    return inslist

class node:
    def __init__(self, name, opcode, param):
        self.name = name
        self.opcode = opcode
        self.param = param
    def __str__(self):
        return "{{name: {}, opcode: {}, param: {}}}".format(
                    self.name,
                    code2name[self.opcode],
                    self.param
                )
    def __repr__(self):
        return self.__str__()

def get_param_value(param):
    if param == "": # no param
        return None
    elif (param[0] == "\"" and param[len(param)-1] == "\""): # string
        param = param[1:len(param)-1]
    else:
        try:
            param = int(param)
        except ValueError:
            try:
                param = float(param)
            except ValueError:
                # name, create NOP
                nop = node(
                    "",
                    name2code["nop"],
                    param
                )
                param = nop
    return param

def gennode(inslist):
    nopdict = {}
    nodelist = []
    for i in inslist:
        name = i.name
        opname = i.opname
        param = i.param

        # classify param # string/integer/float
        paramlist = []
        for p in param:
            pvalue = get_param_value(p)
            if (isinstance(pvalue, node)):
                nopdict[pvalue.param] = pvalue
            if (pvalue != None):
                paramlist.append(pvalue)
        param = paramlist
        # gen node
        code = node(
            name,
            name2code[opname],
            param
        )
        nodelist.append(code)
    orderednodelist = []
    for n in nodelist:
        if (n.name != ""):
            try:
                nop = nopdict[n.name]
                orderednodelist.append(nop)
            except KeyError:
                print("KeyError: {}".format(n.name))
        orderednodelist.append(n)
    return orderednodelist




if __name__ == "__main__":
    i = parse("fibonacci.bytecode")
    n = gennode(i)
    for x in n:
        print(x)
    pdb.set_trace()
