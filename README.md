## 一、架构设计

#### 头文件Stack.h

​		用一个MyStack类来用数组实现栈的基本操作，其中包含栈的push，pop，top的基本操作，并且添加了show函数用来将栈里面的数据都输出出来，还有添加了size函数用来输出当前栈的大小，fshow函数，用来把栈里面的内容全部输入到文本文件里面。

#### 头文件Traveler.h

​		旅客类，其中包含的成员变量有 ：m_name旅客姓名，m_sex旅客性别，m_workplace旅客工作单位，m_office旅客职务，m_from旅客来自何处，m_id旅客身份证号，room_num旅客房号，bed_code旅客床号，Empty_bed_num旅客床号栈，m_age旅客年龄，in_date住店时间，out_date离店时间并且包含showInfo函数以及showInfo_5函数用来显示旅客的信息。

#### 源文件Traveler.cpp

​		旅客类的构造函数traveler将输入的旅客姓名、性别、工作单位、职务、来自何处、身份证号、旅客房号、床号、旅客床号栈、年龄、住店时间、离店时间等信息进行读入，showInfo和showInfo_5函数实现了简单的输出旅客信息的功能，其中用到了结构体的show函数进行文件的读取。

#### 头文件Room.h

​		构建一个名为room的结构体，其中包含了Empty_bed_num空床栈、string sex房间性别、string room_rank房间等级、string room_num房号、string bed_sum床位总数、string bed_count空床位数、string bed_using_num占用床位数、string Bed_message空床位信息数组、string money_one单床每天费用、string money_all包房每天费用、struct Link* next = NULL指针。以show_bednum函数来从头遍历输入节点，用creatlink 函数来创建链表，用input_new函数和finput_new函数通过while来实现一个一个节点的循环将文本文件里面通过switch有选择的将数据读到链表里面，在用一个床位信息的数组来储存这些信息，还将string类型的床位总数转化为整形，来实现根据文件内容把链表初始化把文件里面的内容输入到链表里。

#### 	头文件Time.h

​		用MOUTHDAYS来储存每个月份拥有的天数，例如一月拥有31天，MouthDays函数用来查看是否为闰年，Transformation函数用来输入的时间字符串分割成年月日和小时，然后分别储存在各变量中。getTime用来获取旅客住店时的时间。然后退房的时候DataMinus计算住店时间和离店时间的时间差，根据年月日先返回天数，再根据根据时分秒判断是否满足12小时，若满足十二小时则算一天，若不满足则算半天。

#### 源文件Hotel.cpp

​		首先声明一个布尔类型的全局变量flag用来记录是否输入过个人信息，用来表示不能重复入住。read1函数用来读取room文本文件的信息，并且将其输出出来。read函数用来创建链表来读取room文件里面的信息。

​		hotel类的构造函数hotel通过traveler文本文件是否存在还有是否能打开，里面是数据是否为空，来确定其旅客入住的人数，假如traveler文本文件不存在或者存在但是其数据为空则证明其没有旅客入住，旅馆的所有入住人数为0；假如文件存在则记录当前文件里面的旅客数据，并且将其保存到一个数组里面，创建三个等级的空房间栈链表用来跟根据文件内容来确定旅客所入住的房间等级，将traceler文本文件里面的数据保存在等级一、等级二、等级三的空房间栈里面（此处用到了链表结构以及栈的push函数将旅客入栈）

​		Add_Tra函数实现添加旅客的功能，其首先声明addNum用来记录将要入住的人数，输入完成后将之前的旅客人数m_Trannum加上addNum就是当前的旅客人数（这里运用的是new动态申请内存的方式），确定人数之后，通过一个for循环，将旅客的信息保存到动态申请的数组里面，并且用getTime函数来获取当前电脑的时间，来代表旅客入住时候的时间，将入住旅客信息保存后用delete来释放掉new出来的空间。

​		Save函数将Add_Tra函数申请的动态数组里面的旅客信息保存到traveler文本文件里面。get_Tranum函数是将traveler文本文件的旅客人数统计一下。init_Tra函数用来将读入的traveler文本文件里面旅客信息数据初始化数组里面，因为程序关掉之后重新打开的话需要这个get_Tranum函数将traveler文本文件里面的旅客信息重新读入到数组里面，以便于后面查找旅客。

​		Show_Tra函数是查找旅客 信息的函数，假如traveler文本文件数据为空，则输出入住人口为0，有数据的话则输出旅客信息数据。Show_Menu函数是输出旅馆程序的主页面，其中用到了read函数来输出房间的信息。

​		ExitSystem函数是退出程序的功能，其退出程序后输出欢迎下次使用的字样。Inroomfile函数是更新房间的内容函数，首先创建三个等级的链表对应三个等级的房间，用while来将三个等级的房间的内容进行更新（当旅客入住到旅馆中后需要更新其房间的内容）。

​		in_servel函数用来实现程序的订房功能，订房分为单床服务、包房服务还有预定房间，通过一个if语句来判断接下来需要的操作。如果输入的是1则进行单床服务的功能，进行单床服务首先需要选择入住房间的等级，假如选择入住等级一的房间则对应房间等级的栈为空，则代表没有房间，让其选择入住其他等级的房间或者是返回到菜单系统中去，假如对应的栈部位空，则说明有房间，这时候判断是否旅客性别与房间性别相同,或者一个人也没有并且房间里面的床位，将房号传递给旅客，并且把房号传递给旅客，之后将空床栈弹出床位给旅客房号栈，入住后进行bed_count[0] -= 1将住进来则空床位减一、占用床位数加一，之后把房间性别标记为顾客性别，之后在使用inroomfile函数来更新room房间文件的内容用save函数来保存room文本文件假如房间不符合性别要求，则看一下个房间，并且将pop弹出来的房间放在临时栈内，倘若每一个房间都不符合要求，则输出床铺已满，选择其他的住房服务，并且可以选择返回主菜单。假如输入的是数字2则进行包房服务，首先输入要包房的房间等级，然后查找对应房间栈的情况，倘若栈为空则代表没哟与空房，再次退出到主菜单区，倘若栈不为空，则说明又空房间可以包房，再次将房号给旅客、空床栈弹出床位给旅客房号栈、将此房间空床栈清空、住进来后则空床位变0、占用床位数变为床位总数、把房间性别标记为顾客性别。假如房间床位满了，则更新最原本的空房栈、用inroomfile函数更新房间文件内容，用save()函数更新旅客文件内容。倘若每一个房间都不符合包房要求，则让旅客选择是否继续选择其他等级的房间入住，或者返回主菜单。假如输入数字为3则进行预定房间的功能。预定房间功能首先用一个string类型的数据in_data来输入入店的时间，在读取其入住的房间等级，倘若选择的为等级一的房间，则查看等级一的房间栈是否为空，倘房间栈若为空，则证明无空房间，则返回旅客选择是否选择其他等级的房间入住，或者返回程序主菜单。若房间栈不为空，说明有空房间，若旅客性别与房间性别相同,或者一个人也没有并且房间里面的床位则将把房号给旅客，空床栈弹出床位给旅客房号栈，然后保存文件内容。若每个房间都不符合性别要求则返回旅客选择是否选择其他等级的房间入住，或者返回程序主菜单。

​		用in_serve2函数实现退房的功能，用布尔类型flag来检查旅客是否检索到，在输入想要退房间的的旅客的姓名，用for循环从数组开始循环找到想要退房的那个人，用m_TraArray[i]->out_date = getTime()记录当前离店时间，并且输出旅客需要支付的费用为，然后记录退房旅客的床数还有床号栈，再次用save函数来保存此时的文件状态，当检索到等级一号的房间后旅客后进行：占用床位数减旅客占的床、空床位数加旅客占的床，假如房间变空，则将房间的性别变为0（0代表空），然后将床号放入到空房间栈里面。倘若flag为0则说明没有找到这个旅客，没有查找到此旅客。用In_serve5函数来实现查找旅客信息的功能，当输入数字1时再次用布尔类型flag定义标志检索是否能检测的到，再用for循环遍历数组，来查找某一个旅客。当输入数组2时，用之前的Show_Tra函数来显示所有的旅客信息。

## 二、主要模块流程图

​		当旅客进入旅店入住系统的时候，假如旅客选择的是入住旅店的服务，则程序会读进去旅客的选择，这个时候程序就会让旅客输入旅客的个人信息，如旅客的姓名、年龄、身份证号码等等并且让旅客选择入住的房间等级，如果拥有对应等级的房间则入住成功，假如没有则让旅客选择是否选择其他等级的房间，如果旅客选择否则退出系统。流程图如图1所示。

<img src="file:///C:\Users\天选之人\AppData\Local\Temp\ksohtml22928\wps92.jpg" alt="img" style="zoom: 67%;" /> 

**图1.选择入住旅馆的流程图**

​		当旅客选择的是退房系统的时候，首先程序会提示旅客填入需要退房服务的旅客姓名，之后在读取输入的需要退房服务的旅客，此时系统会查找是否有此旅客，假如查找到次旅客则退房成功，假如没有查找到此旅客，则选择是否继续搜索旅客，选择是时则再次读取输入的旅客姓名和房间号码，假如选择否则退出程序。

<img src="file:///C:\Users\天选之人\AppData\Local\Temp\ksohtml22928\wps93.jpg" alt="img" style="zoom:67%;" /> 

**图2.选择退房服务的流程图**

​		当旅客选择的是其他服务的时候，首先程序会提示选择查找某旅客信息的服务或者是显示所有入住旅客信息的服务，当选择查找某一旅客信心服务时，会读取输入的需要查找旅客的姓名以及房号，系统接受到后会查找是否存在此旅客，假如存在则显示此旅客信息，如果没有此旅客则让其选择是否继续查找，选择是时再次输入需要查找的旅客姓名以及房号，若选择否，则退出系统，倘若开始选择的是显示所有入住旅客信息服务功能，则显示所有旅客信息。

<img src="file:///C:\Users\天选之人\AppData\Local\Temp\ksohtml22928\wps94.jpg" alt="img" style="zoom:67%;" /> 

**图3.选择其他服务时候的流程图**