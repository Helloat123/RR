import tkinter as tk
from subprocess import Popen, PIPE
import select

def execute_rr():
    input_value = cxcode.get("1.0", tk.END)  # 获取第一个文本框的内容作为输入值
    print(input_value)
    command = "./rr"  # rr命令
    proc1 = Popen(command, stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True, text=True)
    stdout, stderr = proc1.communicate(input=input_value + '\n', timeout=5)  # 发送输入值并关闭输入流
    result = stdout
    print(result)
    pcode.delete('1.0', tk.END)  # 清空第二个文本框
    pcode.insert(tk.END, result)  # 在第二个文本框中显示rr的返回值

def execute_ri():
    input_value=pcode.get("1.0",tk.END)
    command="./ri"
    global process
    process=Popen(command,stdin=PIPE,stdout=PIPE,stderr=PIPE,shell=True,text=True)
    if process.poll() is None: print("running");
    process.stdin.write(input_value)
    process.stdin.flush()
    root.after(10,read_output)

def read_output():
    #global process
    if process.poll() is None:
        process.stdout.flush()
        ready_to_read,_,_=select.select([process.stdout.fileno()],[],[],0.1)
        if ready_to_read:
            out=process.stdout.readline()
            print(out)
            #output.delete('1.0',tk.END)
            output.insert(tk.END,out)
        root.after(10,read_output)

def next_line():
    #global process
    command="next\n"
    process.stdin.write(command)
    process.stdin.flush()
    #root.after(100,read_output)

def continue_run():
    #global process
    command="continue\n"
    process.stdin.write(command)
    process.stdin.flush()
    #root.after(100,read_output)

def quit_ri():
    process.stdin.write("quit\n")
    process.stdin.flush()
    output.delete('1.0',tk.END)
    pcode.delete('1.0',tk.END)

def get_input():
    input_value=inpu.get()
    process.stdin.write(input_value+'next\n')
    process.stdin.flush()


root = tk.Tk()

# code text
cxcode = tk.Text(root, height=8, width=100)
cxcode.pack()

# pcode text
pcode = tk.Text(root, height=12, width=100)
pcode.pack()

# input text
inpu = tk.Entry(root,width=100)
inpu.pack()

# output text
output = tk.Text(root,height=20,width=100)
output.pack()

# compile button
comp = tk.Button(root, text="Compile", command=execute_rr)
comp.pack()

# run button
run = tk.Button(root,text="run",command=execute_ri)
run.pack()

# input button
inp=tk.Button(root,text="input",command=get_input)
inp.pack()

# next button
nxt = tk.Button(root,text="next",command=next_line)
nxt.pack()

# continue button
con = tk.Button(root,text="continue",command=continue_run)
con.pack()

# quit button
qui = tk.Button(root,text="quit ri",command=quit_ri)
qui.pack()

root.mainloop()

