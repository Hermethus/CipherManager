#TODO
#直接保存，无需另存为
#未保存提醒
#备注功能
#多归属地


from ciphermamager import CipherManager
import hashlib
from tkinter import *
from tkinter import messagebox, filedialog
import pyperclip


class cmUI(Tk):
    
    def __init__(self):
        super().__init__()
        self.resizable(width=False, height=False)
        self.title("密码管理v1.1")
        #self.iconbitmap('icon.ico')#窗口左上角图标，无法打包进程序
                                    #其实可以打包，需要
                                    #将图片转为base64编码存进.py文件
                                    #再import再写入.ico文件再删除，很麻烦，没有必要
        self.setupUI()
        self.cm = None
        self.current_select = None
        
    def setupUI(self):
        #菜单
        self.menu = Menu(self)
        self.config(menu=self.menu)
        
        self.filemenu = Menu(self.menu, tearoff=False)
        self.filemenu.add_command(label="新建空白密码本", command=self.new)
        self.filemenu.add_command(label="从明文新建", command=self.new_from_file)
        self.filemenu.add_command(label="打开密文文件", command=self.open_file)
        self.filemenu.add_separator()
        self.filemenu.add_command(label="保存为密文文件", command=self.save, state=DISABLED)
        self.filemenu.add_command(label="导出明文文件", command=self.save_as_plain, state=DISABLED)
        self.filemenu.add_separator()
        self.filemenu.add_command(label="关闭文件", command=self.close_file_disable, state=DISABLED)
        
        self.passwordmenu = Menu(self.menu, tearoff=False)
        self.passwordmenu.add_command(label="修改密码",
                                      command=self.change_password, state=DISABLED)
        
        self.helpmenu = Menu(self.menu, tearoff=False)
        self.helpmenu.add_command(label="帮助", command=self.get_help)
        self.helpmenu.add_command(label="关于我们", command=self.about)
        
        self.menu.add_cascade(label="文件", menu=self.filemenu)
        self.menu.add_cascade(label="密码", menu=self.passwordmenu)
        self.menu.add_cascade(label="关于", menu=self.helpmenu)
        
        #布局
        #左半边
        self.left_frame = Frame(self, width=300, height=500, relief=GROOVE)
        self.left_frame.grid(row=0, column=0)
        
        #左半边-搜索框部分
        self.search_frame = LabelFrame(self.left_frame, text="搜索", width=300, height=100)
        self.search_frame.grid(row=0, padx=5, pady=5)
        
        self.search = StringVar()
        self.search_entry = Entry(self.search_frame, width=20,
                                  textvariable=self.search, state=DISABLED)
        self.search_entry.grid(row=0, column=0, padx=5, pady=5)
        
        self.search_button = Button(self.search_frame, text="搜索", 
                                    command=self.search_item, state=DISABLED)
        self.search_button.grid(row=0, column=1, padx=5, pady=5)
        
        #左半边-用户名
        self.username_frame = LabelFrame(self.left_frame, text="用户名", 
                                         width=300, height=100)
        self.username_frame.grid(row=1, padx=5, pady=5)
        
        self.username = StringVar()
        self.username_entry = Entry(self.username_frame, width=20, 
                                    textvariable=self.username, state=DISABLED)
        self.username_entry.grid(row=0, column=0, padx=5, pady=5)
        
        self.username_button = Button(self.username_frame, text="复制", 
                                      command=self.copy_username, state=DISABLED)
        self.username_button.grid(row=0, column=1, padx=5, pady=5)
        
        #左半边-密码
        self.password_frame = LabelFrame(self.left_frame, text="密码", 
                                         width=300, height=100)
        self.password_frame.grid(row=2, padx=5, pady=5)
        
        self.password = StringVar()
        self.password_entry = Entry(self.password_frame, width=20, show="*",
                                    textvariable=self.password, state=DISABLED)
        self.password_entry.grid(row=0, column=0, padx=5, pady=5)
        
        self.password_button = Button(self.password_frame, text="复制", 
                                      command=self.copy_password, state=DISABLED)
        self.password_button.grid(row=0, column=1, padx=5, pady=5)
        
        #左半边-按钮
        self.button_frame = Frame(self.left_frame, width=300, height=100)
        self.button_frame.grid(row=3, padx=5, pady=5)
        
        self.add_button = Button(self.button_frame, text="添加新的一项", 
                                 command=self.add, state=DISABLED)
        self.add_button.grid(row=0, column=0, padx=5, pady=5)
        
        self.del_button = Button(self.button_frame, text="删除选中的项", 
                                 command=self.delete, state=DISABLED)
        self.del_button.grid(row=0, column=1, padx=5, pady=5)
        
        self.modify_button = Button(self.button_frame, text="修改选中的项", 
                                 command=self.modify, state=DISABLED)
        self.modify_button.grid(row=1, column=0, padx=5, pady=5)
        
        self.clean_button = Button(self.button_frame, text="    清空界面    ", 
                                 command=self.clean_all, state=DISABLED)
        self.clean_button.grid(row=1, column=1, padx=5, pady=5)
        
        #右半边
        self.right_frame = LabelFrame(self, text="搜索结果", width=300, height=500)
        self.right_frame.grid(row=0, column=1, padx=5)
        
        self.sb = Scrollbar(self)
        self.lb = Listbox(self.right_frame, height=13, 
                          selectmode=SINGLE, yscrollcommand=self.sb.set)
        self.lb.grid(row=0, column=0, padx=5, pady=5)
        self.lb.bind("<Double-Button-1>", self.get_info)
        self.sb.config(command=self.lb.yview)

    
    def new(self):
        self.open_path = None
        self._new_password()
    
    def new_from_file(self):
        self.open_path = filedialog.askopenfilename(
                title='打开明文文件', filetypes=[('TXT文本文档', '*.txt'), ('所有文件', '*.*')])
        if self.open_path:
            self._new_password()
    
    def _new_password(self):
        self.top = Toplevel(self)
        self.top.attributes("-topmost", True)
        
        self.top_label1 = Label(self.top, text="请输入密码：")
        self.top_label1.grid(row=0, column=0, padx=5, pady=5, sticky=W)
        self.top_password_entry = Entry(self.top, show="*")
        self.top_password_entry.grid(row=0, column=1, padx=5, pady=5)
        
        self.top_label2 = Label(self.top, text="再次输入密码：")
        self.top_label2.grid(row=1, column=0, padx=5, pady=5, sticky=W)
        self.top_password_verify = Entry(self.top, show="*")
        self.top_password_verify.grid(row=1, column=1, padx=5, pady=5)
        
        self.top_button = Button(self.top, text="    确认    ", command=self._compare_password)
        self.top_button.grid(row=2, column=0, columnspan=2, padx=5, pady=5)
    
    def _compare_password(self):
        if self.top_password_entry.get()==self.top_password_verify.get():
            pw = self.top_password_entry.get()
            self.cm = CipherManager(password=pw, file_path=self.open_path)
            
            self.open_file_enable()
        else:
            messagebox.showerror(title='错误', message="两次输入密码不一样！")
        self.top.destroy()
    
    def open_file(self):
        self.open_path = filedialog.askopenfilename(
                title='打开加密文件', filetypes=[('CIPHER文件', '*.cipher'), ('所有文件', '*.*')])
        if self.open_path:
            self._enter_password()

    def _enter_password(self):
        self.top = Toplevel(self)
        self.top.attributes("-topmost", True)
        
        self.top_label1 = Label(self.top, text="请输入密码：")
        self.top_label1.grid(row=0, column=0, padx=5, pady=5, sticky=W)
        self.top_password_entry = Entry(self.top, show="*")
        self.top_password_entry.grid(row=0, column=1, padx=5, pady=5)
        
        self.top_button = Button(self.top, text="    确认    ", command=self._verify_password)
        self.top_button.grid(row=1, column=0, columnspan=2, padx=5, pady=5)
    
    def _verify_password(self):
        pw = self.top_password_entry.get()
        try:
            self.cm = CipherManager(password=pw, file_path=self.open_path, new=False)
            self.open_file_enable()
        except Exception as e:
            messagebox.showerror(title='错误', message="文件或密码错误！")
            print(e)
        self.top.destroy()
        
    def get_info(self, event):
        self.current_select = self.lb.get(ACTIVE)
        username, password = self.cm.get(self.current_select)
        self.username.set(username)
        self.password.set(password)

    def save(self):
        path = filedialog.asksaveasfilename(
                title='保存为加密文件', filetypes=[('CIPHER文件', '*.cipher'), ('所有文件', '*.*')])
        self.cm.save(path)
    
    def save_as_plain(self):
        path = filedialog.asksaveasfilename(
                title='保存为txt文件', filetypes=[('TXT文件', '*.txt'), ('所有文件', '*.*')])
        self.cm.save_as_plain(path)
        
    def change_password(self):
        self.clean_all()
        self.top = Toplevel(self)
        self.top.attributes("-topmost", True)
        
        self.top_label0 = Label(self.top, text="请输入旧密码：")
        self.top_label0.grid(row=0, column=0, padx=5, pady=5, sticky=W)
        self.top_old_password_entry = Entry(self.top, show="*")
        self.top_old_password_entry.grid(row=0, column=1, padx=5, pady=5)
        
        self.top_label1 = Label(self.top, text="请输入新密码：")
        self.top_label1.grid(row=1, column=0, padx=5, pady=5, sticky=W)
        self.top_password_entry = Entry(self.top, show="*")
        self.top_password_entry.grid(row=1, column=1, padx=5, pady=5)
        
        self.top_label2 = Label(self.top, text="再次输入密码：")
        self.top_label2.grid(row=2, column=0, padx=5, pady=5, sticky=W)
        self.top_password_verify = Entry(self.top, show="*")
        self.top_password_verify.grid(row=2, column=1, padx=5, pady=5)
        
        self.top_button = Button(self.top, text="    确认    ", command=self._change_password)
        self.top_button.grid(row=3, column=0, columnspan=2, padx=5, pady=5)
    
    def _change_password(self):
        m = hashlib.md5()
        m.update(bytes(self.top_old_password_entry.get(), encoding="utf-8"))
        old_password = m.hexdigest()
        if old_password!=self.cm.password:
            messagebox.showerror(title='错误', message="密码输入错误！")
        elif self.top_password_entry.get()!=self.top_password_verify.get():
            messagebox.showerror(title='错误', message="两次输入密码不一样！")
        else:
            new_password = self.top_password_entry.get()
            self.cm.set_password(new_password)
            messagebox.showinfo(title='信息', message="修改成功！")
        self.top.destroy()
    
    def about(self):
        messagebox.showinfo(title='关于',
                            message="""欢迎使用这个很简单的密码管理软件！
==============================
2020.5.18更新：
新增了明文导出功能。
密文格式在不同版本中不兼容，明文格式兼容。
支持utf-8编码，账号归属和用户名密码可使用中文。
==============================
由于使用python编写，打开速度可能较慢。
将来可能使用C#重构代码。
如果发现任何bug，欢迎邮件沟通。
邮箱：dzxx_ld@sjtu.edu.cn
\t\tHermethus
\t\t2020/4/11""")
    
    def get_help(self):
        messagebox.showinfo(title='帮助', message="""·进行相关操作之前，应该先读入或新建密码本文件。
·明文读入文件格式：
     每次读入一行，每行中账号归属、用户名、密码用空格分隔。
     如果上述内容中包含空格的，不应用文件读入，建议手动输入。
·查找对应归属的账户信息
     使用搜索寻找关键词，搜索结果会列在右边的列表中。
     *(星号)是唯一通配符，匹配所有内容，但是不建议使用。
     双击可以使选中项的用户名和密码显示在左边，单击不行。
     密码不能通过ctrl+C复制，使用时单击复制可以复制到剪贴板中。
""")
    
    def search_item(self):
        self.lb.delete(0, END)
        self.username.set("")
        self.password.set("")
        self.current_select = None
        
        if self.cm and self.search.get():
            result = self.cm.search(self.search.get())
            for item in result:
                self.lb.insert(END, item)
        self.search.set("")
    
    def copy_username(self):
        if self.current_select:
            pyperclip.copy(self.cm.code_dict[self.current_select][0])
            messagebox.showinfo(title='提示', message='用户名复制成功！')
        else:
            messagebox.showerror(title='错误', message='用户名复制不成功，请重新双击选中一项！')
    
    def copy_password(self):
        if self.current_select:
            pyperclip.copy(self.cm.code_dict[self.current_select][1])
            messagebox.showinfo(title='提示', message='密码复制成功！')
        else:
            messagebox.showerror(title='错误', message='密码复制不成功，请重新双击选中一项！')
    
    def modify(self):
        if not self.current_select:
            messagebox.showerror(title='错误', message="修改不成功，请重新双击选中一项！")
            return
        
        self.top = Toplevel(self)
        self.top.attributes("-topmost", True)
        
        self.top_label1 = Label(self.top, text="请输入用户名：")
        self.top_label1.grid(row=1, column=0, padx=5, pady=5, sticky=W)
        self.top_username_entry = Entry(self.top)
        self.top_username_entry.grid(row=1, column=1, padx=5, pady=5)
        
        self.top_label2 = Label(self.top, text="请输入密码：")
        self.top_label2.grid(row=2, column=0, padx=5, pady=5, sticky=W)
        self.top_password_entry = Entry(self.top, show="*")
        self.top_password_entry.grid(row=2, column=1, padx=5, pady=5)
        
        self.top_label3 = Label(self.top, text="请再次输入密码：")
        self.top_label3.grid(row=3, column=0, padx=5, pady=5, sticky=W)
        self.top_password_verify = Entry(self.top, show="*")
        self.top_password_verify.grid(row=3, column=1, padx=5, pady=5)
        
        self.top_button = Button(self.top, text="    确认    ", command=self._modify)
        self.top_button.grid(row=4, column=0, columnspan=2, padx=5, pady=5)
    
    def _modify(self):
        if self.top_password_entry.get()!=self.top_password_verify.get():
            messagebox.showerror(title='错误', message="两次输入密码不一样！")
            return
        
        self.cm.modify(self.current_select, self.top_username_entry.get(), 0)
        self.cm.modify(self.current_select, self.top_password_entry.get(), 1)
        self.clean()
        self.top.destroy()
            
        
    def add(self):
        self.top = Toplevel(self)
        self.top.attributes("-topmost", True)
        
        self.top_label0 = Label(self.top, text="请输入账号归属：")
        self.top_label0.grid(row=0, column=0, padx=5, pady=5, sticky=W)
        self.top_title_entry = Entry(self.top)
        self.top_title_entry.grid(row=0, column=1, padx=5, pady=5)
        
        self.top_label1 = Label(self.top, text="请输入用户名：")
        self.top_label1.grid(row=1, column=0, padx=5, pady=5, sticky=W)
        self.top_username_entry = Entry(self.top)
        self.top_username_entry.grid(row=1, column=1, padx=5, pady=5)
        
        self.top_label2 = Label(self.top, text="请输入密码：")
        self.top_label2.grid(row=2, column=0, padx=5, pady=5, sticky=W)
        self.top_password_entry = Entry(self.top, show="*")
        self.top_password_entry.grid(row=2, column=1, padx=5, pady=5)
        
        self.top_label3 = Label(self.top, text="请再次输入密码：")
        self.top_label3.grid(row=3, column=0, padx=5, pady=5, sticky=W)
        self.top_password_verify = Entry(self.top, show="*")
        self.top_password_verify.grid(row=3, column=1, padx=5, pady=5)
        
        self.top_button = Button(self.top, text="    确认    ", command=self._add)
        self.top_button.grid(row=4, column=0, columnspan=2, padx=5, pady=5)
    
    def _add(self):
        if self.top_password_entry.get()!=self.top_password_verify.get():
            messagebox.showerror(title='错误', message="两次输入密码不一样！")
            self.top.destroy()
            return
            
        if not self.cm.add(self.top_title_entry.get(), 
                           self.top_username_entry.get(), self.top_password_entry.get()):
            messagebox.showerror(title='错误', 
                                 message='"{}"已存在！'.format(self.top_title_entry.get()))
        self.top.destroy()
    
    def delete(self):
        if not self.current_select:
            messagebox.showerror(title='错误', message="删除不成功，请重新双击选中一项！")
            return
        victim = self.lb.get(ACTIVE)
        if victim=="":
            messagebox.showerror(title='错误', message="删除不成功，请重新双击选中一项！")
            return
        if messagebox.askyesno(title='提示', message='确定要删除“{}”的内容吗？'.format(victim)):
            self.lb.delete(ACTIVE)
            self.cm.delete(victim)
        self.clean()
        
    def close_file_disable(self):
        self.clean_all()
        self.cm = None
        
        self.filemenu.entryconfig("保存为密文文件", state=DISABLED)
        self.filemenu.entryconfig("导出明文文件", state=DISABLED)
        self.filemenu.entryconfig("关闭文件", state=DISABLED)
        self.passwordmenu.entryconfig("修改密码", state=DISABLED) 
        self.search_button['state'] = 'disabled'
        self.search_entry['state'] = 'disabled'
        self.username_entry['state'] = 'disabled'
        self.username_button['state'] = 'disabled'
        self.password_entry['state'] = 'disabled'
        self.password_button['state'] = 'disabled'
        self.add_button['state'] = 'disabled'
        self.del_button['state'] = 'disabled'
        self.modify_button['state'] = 'disabled'
        self.clean_button['state'] = 'disabled'
        
    def open_file_enable(self):
        self.filemenu.entryconfig("保存为密文文件", state=NORMAL)
        self.filemenu.entryconfig("导出明文文件", state=NORMAL)
        self.filemenu.entryconfig("关闭文件", state=NORMAL)
        self.passwordmenu.entryconfig("修改密码", state=NORMAL) 
        self.search_button['state'] = 'normal'
        self.search_entry['state'] = 'normal'
        self.username_entry['state'] = 'normal'
        self.username_button['state'] = 'normal'
        self.password_entry['state'] = 'normal'
        self.password_button['state'] = 'normal'
        self.add_button['state'] = 'normal'
        self.del_button['state'] = 'normal'
        self.modify_button['state'] = 'normal'
        self.clean_button['state'] = 'normal'
    
    def clean_all(self):
        self.clean()
        self.lb.delete(0, END)
    
    def clean(self):
        self.username.set("")
        self.password.set("")
        self.search.set("")
        self.current_select = None

    
app = cmUI()

mainloop()




