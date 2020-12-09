#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct LNode {  //线性表表（链式结构）结点的定义
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

typedef struct {
    struct {
        char name[30];
        LinkList L;
    } elem[10];
    int length;
    int listsize;
} LISTS;

using namespace std;


//所要使用的函数声明以供使用
int InitList(LinkList &L);

status DestroyList(LinkList &L);

int ClearList(LinkList &L);

status ListEmpty(LinkList L);

int ListLength(LinkList L);

int GetElem(LinkList L, int i, ElemType &e);

int LocateElem(LinkList L, ElemType e);

status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e);

status NextElem(LinkList L, ElemType cur_e, ElemType &next_e);

status ListInsert(LinkList &L, int i, ElemType e);

status ListDelete(LinkList &L, int i, ElemType &e);

status ListTraverse(LinkList L);      //单个线性表的处理
status SaveList(LinkList L, char FileName[]);

status LoadList(LinkList &L, char FileName[]);  //线性表的存储读写操作
status AddList(LISTS &Lists, char ListName[]);

status RemoveList(LISTS &Lists, char ListName[]);

int LocateList(LISTS Lists, char ListName[]);   //多链表的操作

/*--------------------------------------------*/
int main(void) {
    LISTS Lists;
    Lists.length = 0;
    int n;
    int opt = 0;
    char name[30];
    char FileName[30];
    LinkList L, L1, s;
    int op = 1;
    int j;
    int f, e, i, pre, next, p;
    int count = 0;
    int flag;
    L = NULL; //表L置为空
    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. 添加线性表      7. 获取元素的前驱\n");
        printf("    	  2. 清空线性表      8. 获取元素的后继\n");
        printf("    	  3. 线性表判空      9.  插入元素\n");
        printf("    	  4. 线性表长度      10. 删除元素\n");
        printf("    	  5. 获取元素        11. 遍历线性表\n");
        printf("    	  6. 查找元素        12. 保存线性表\n");
        printf("    	  13.加载线性表      14. 删除线性表\n");
        printf("    	  15.查找线性表      16.遍历多线性表\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~16]:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("请输入要添加的线性表的个数");
                scanf("%d", &n);
                while (n--) {
                    printf("请输入要添加的线性表的名称\n");
                    scanf("%s", name);
                    AddList(Lists, name);  //增加函数的使用
                    printf("线性表添加成功,请输入线性表的元素，以0结尾\n");
                    scanf("%d", &e);
                    i = 0;
                    while (e) {
                        ListInsert(Lists.elem[Lists.length - 1].L, i + 1, e);
                        scanf("%d", &e);
                        i++;
                    }
                }
                for (n = 0; n < Lists.length; n++) {
                    printf("%s ", Lists.elem[n].name);
                    ListTraverse(Lists.elem[n].L);
                    printf("\n");
                }
                getchar();
                printf("\n");
                break;
            case 2:  // 清空线性表 done
                printf("请输入你想要清空的线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Lists.length; i++) {
                    j = strcmp(Lists.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行删除操作
                        flag = ClearList(Lists.elem[i].L);
                        if (flag == ERROR) printf("该线性表已经为空！");
                        if (flag == OK) printf("已清空该线性表");
                        if (flag == INFEASIBLE) printf("ERROR");
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 3: //判断是否为空 done
                printf("请输入线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Lists.length; i++) {
                    j = strcmp(Lists.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行删除操作
                        flag = ListEmpty(Lists.elem[i].L);
                        if (flag == INFEASIBLE) printf("ERROR");
                        if (flag == true) printf("该线性表为空");
                        if (flag == false) printf("该线性表不为空");
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 4:  //求表长  done
                printf("请输入线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Lists.length; i++) {
                    j = strcmp(Lists.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行删除操作
                        flag = ListLength(Lists.elem[i].L);
                        printf("此线性表的表长为：%d", flag);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 5:  //查找元素 done
                printf("请输入要进行查找元素线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Lists.length; i++) {
                    j = strcmp(Lists.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行删除操作
                        printf("请输入要查找的元素的位置");
                        scanf("%d", &p);
                        j = GetElem(Lists.elem[i].L, p, e);  //查找函数的使用
                        if (j == OK) printf("获取元素成功!位置%d的元素是%d", p, e);
                        if (j == ERROR) printf("ERROR");
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 6: //查找元素位置 done
                printf("请输入要进行查找元素线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Lists.length; i++) {
                    j = strcmp(Lists.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行查找操作
                        printf("请输入要查找的元素");
                        scanf("%d", &e);
                        j = LocateElem(Lists.elem[i].L, e);  //查找函数的使用
                        if (j == ERROR) printf("ERROR");
                        else printf("查找元素成功!元素%d的位置%d", e, j);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 7: //查找前驱元素 done
                printf("请输入要进行查找前驱元素线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Lists.length; i++) {
                    j = strcmp(Lists.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行查找操作
                        printf("请输入要查找前驱的元素");
                        scanf("%d", &e);
                        j = PriorElem(Lists.elem[i].L, e, pre);  //查找函数的使用
                        if (j == ERROR) printf("ERROR");
                        else printf("查找元素成功!元素%d的前驱为%d", e, pre);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 8:  //查找后继元素 done
                printf("请输入要进行查找后继元素线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Lists.length; i++) {
                    j = strcmp(Lists.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行查找操作
                        printf("请输入要查找后继的元素");
                        scanf("%d", &e);
                        j = NextElem(Lists.elem[i].L, e, next);  //查找函数的使用
                        if (j == ERROR) printf("ERROR");
                        else printf("查找元素成功!元素%d的后继为%d", e, next);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 9:  //插入元素  done
                printf("请输入要进行插入元素线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Lists.length; i++) {
                    j = strcmp(Lists.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行查找操作
                        printf("请输入要插入的位置");
                        scanf("%d", &p);
                        printf("请输入要插入的元素");
                        scanf("%d", &e);
                        j = ListInsert(Lists.elem[i].L, p, e);  //查找函数的使用
                        printf("%s\n", j == OK ? "OK" : j == ERROR ? "ERROR" : "OVERFLOW");
                        ListTraverse(Lists.elem[i].L);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 10:  //元素的删除操作 done
                printf("请输入要进行删除元素线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Lists.length; i++) {
                    j = strcmp(Lists.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行查找操作
                        printf("请输入要删除的位置");
                        scanf("%d", &p);
                        j = ListDelete(Lists.elem[i].L, p, e);
                        if (j == ERROR) printf("ERROR\n");
                        if (j == OK) printf("OK\n%d\n", e);
                        ListTraverse(Lists.elem[i].L);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 11:  //线性表的遍历操作 done
                printf("请输入要进行遍历线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Lists.length; i++) {
                    j = strcmp(Lists.elem[i].name, name);
                    if (j == 0) {
                        printf("遍历之后的结果为:\n");
                        j = ListTraverse(Lists.elem[i].L);
                        if (j == OK && !Lists.elem[i].L->next) printf("空线性表\n");
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 12:  //文件保存 done
                printf("请输入要保存的线性表的名字");
                scanf("%s", name);
                printf("请输入文件存储的地址");
                scanf("%s", FileName);
                for (i = 0; i < Lists.length; i++) {
                    j = strcmp(Lists.elem[i].name, name);
                    if (j == 0) {
                        j = SaveList(Lists.elem[i].L, FileName);
                        printf("保存成功");
                        break;
                    }
                }
                if (i >= Lists.length) printf("没有相应的线性表");
                getchar();
                getchar();
                break;
            case 13:
                printf("请输入要读取的文件地址");
                scanf("%s", FileName);
                printf("请输入要保存的线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Lists.length; i++) {
                    j = strcmp(Lists.elem[i].name, name);
                    if (j == 0) {
                        while (Lists.elem[i].L) {
                            s = Lists.elem[i].L->next;
                            free(Lists.elem[i].L);
                            Lists.elem[i].L = s;
                        }
                        j = LoadList(Lists.elem[i].L, FileName);
                        if (j == OK) printf("读取成功");
                    }
                    break;
                }
                for (s = Lists.elem[i].L->next; s; s = s->next)
                    printf("%d ", s->data);
                getchar();
                getchar();
                break;
            case 14:  //删除线性表 done
                printf("请输入要删除的线性表的名字");
                scanf("%s", name);
                if (RemoveList(Lists, name) == OK) printf("删除成功请使用功能16查看删除后的结果\n");
                else printf("删除失败");
                getchar();
                getchar();
                break;
            case 15:  //查找线性表
                printf("请输入要查找的线性表的名字");
                scanf("%s", name);
                if (n = LocateList(Lists, name)) {
                    printf("查找成功%s ", Lists.elem[n - 1].name);
                    ListTraverse(Lists.elem[n - 1].L);
                } else printf("查找失败\n");
                getchar();
                getchar();
                break;
            case 16:
                for (i = 0; i < Lists.length; i++) {
                    printf("%s ", Lists.elem[i].name);
                    ListTraverse(Lists.elem[i].L);
                    printf("\n");
                }
                if (Lists.length == 0) printf("多链表为空！");
                getchar();
                getchar();
                break;
            case 0:
                break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 1;
}//end of main()

// 初始化线性表,构造一个空线性表
status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L) return INFEASIBLE;
    L = (LinkList) malloc(sizeof(LNode));
    L->next = NULL;
    return OK;

    /********** End **********/
}  //case1

//初始条件：线性表已存在,操作结果：销毁线性表
status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if (!L) return INFEASIBLE;
    LinkList p = L, q = p->next;
    while (q != NULL) {
        free(p);
        p = q;
        q = p->next;
    }
    free(p);
    L = NULL;
    return OK;
    /********** End **********/
}
//case 2

/*初始条件：线性表存在;操作结果：清空线性表
（将当前元素个数赋值0，遍历不出任何一个元素，相当于清空线性表）*/
status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    LinkList p = L->next, q;
    if (!p) return ERROR;
    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
    return OK;
    /********** End **********/
}

//case 3

/*初始条件：线性表存在
操作结果：线性表为空返回true，不为空返回false*/
status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    if (L->next == NULL)
        return true;
    else return false;

    /********** End **********/
}
//case 4

//获取线性表当前元素个数
//初始条件：线性表已存在
//操作结果：返回线性表当前元素个数
int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i = 0;//用于计数
    if (!L) return INFEASIBLE;
    LinkList p = L;
    while (p->next != NULL) {
        i++;
        p = p->next;
    }
    return i;

    /********** End **********/
}
//case 5

//获得指定位置的数据元素
//初始条件：线性表存在
//操作结果：获得指定位置的数据元素并赋值给e
status GetElem(LinkList L, int i, ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    LinkList p = L->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        ++j;
    }
    if (!p || j > i) return ERROR;
    e = p->data;
    return OK;
    /********** End **********/
}
//case 6

//定位元素（获得符合一定条件的数据元素的位序）
//初始条件：线性表已存在
//操作结果：返回L中第一个与e满足关系的元素的位序,若不存在返回0
status LocateElem(LinkList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    int i = 0;
    LinkList p = L->next;
    while (p) {
        i++;
        if (p->data == e) /* 找到这样的数据元素 */
            return i;
        p = p->next;
    }
    return 0;
    /********** End **********/
}
//case 7

//返回要查找的位置元素的前驱
status PriorElem(LinkList L, ElemType e, ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    if (L->next == NULL) return ERROR;
    if (L->next->data == e) return ERROR;
    LinkList p = L->next;
    while (p->next) {
        if (p->next->data == e) {
            pre = p->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
    /********** End **********/
} //case 8

//初始条件：线性表已存在，数据元素存在后继
//操作结果：查找数据元素，若线性表中有该元素且后继存在，将后继拷贝给一个与数据元素数据类型相同的变量；若后继不存在，上述变量无定义
status NextElem(LinkList L, ElemType e, ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    if (L->next == NULL) return ERROR;
    LinkList p = L->next;   //此时p为第一个节点
    while (p->next) //判断p是否是最后一个节点 如果p是最后一个节点则跳出循环 返回ERROR
    {
        if (p->data == e) //匹配节点 匹配成功返回后继
        {
            next = p->next->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
    /********** End **********/
}
//case 9

//插入一个数据元素
//初始条件：线性表存在
//操作结果：在L中第i个元素之前插入新的元素e，L的长度加1
status ListInsert(LinkList &L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    if (i <= 0) return ERROR;
    LinkList p = L;
    int j = 0;
    while (p && j < i - 1) {
        p = p->next;
        if (j > i || !p) return ERROR;
        j++;
    }
    LinkList s = (LinkList) malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
    /********** End **********/
}
//case10

//删除元素
//初始条件：线性表已存在
//操作结构：删除第i个数据元素并返回其值，L的长度减1
status ListDelete(LinkList &L, int i, ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    LinkList p = L->next, q;
    int l = 0, j = 1;
    while (p)  //求线性表的长度
    {
        l++;
        p = p->next;
    }
    p = L->next;
    if (p == NULL) return ERROR; //如果线性表为空 返回错误
    if (i < 1 || i > l) return ERROR;  //如果i不合法返回错误
    //执行删除元素的操作
    for (j = 1; j < i - 1; j++) p = p->next;
    q = p;
    p = p->next; //获取要删除的节点p及它的前继q
    e = p->data;  //取要删除的节点的元素
    q->next = p->next; //删除节点
    free(p);
    return OK;
    /********** End **********/
}

//case 11

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L) return INFEASIBLE;
    LinkList p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    return OK;
    /********** End **********/
}

status SaveList(LinkList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (!L) return INFEASIBLE;
    int length = 0;
    LinkList s = L->next, p = L->next;
    while (s) {
        length++;
        s = s->next;
    }
    FILE *fp;
    if ((fp = fopen(FileName, "wb")) == NULL) {
        printf("File open error\n ");
        return 1;
    }
    while (length--) {
        fwrite(&p->data, sizeof(ElemType), 1, fp);
        p = p->next;
    }
    fclose(fp);
    return OK;
    /********** End **********/
}

status LoadList(LinkList &L, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if (L) return INFEASIBLE;
    L = (LinkList) malloc(sizeof(LNode));
    L->next = NULL;
    LNode *s, *r = L;
    FILE *fp;
    if ((fp = fopen(FileName, "rb")) == NULL) {
        printf("File open error\n ");
        return 1;
    }
    s = (LNode *) malloc(sizeof(LNode));
    while (fread(&s->data, sizeof(ElemType), 1, fp)) {
        r->next = s;
        r = s;
        s = (LNode *) malloc(sizeof(LNode));
    }
    r->next = NULL;
    fclose(fp);
    return OK;
    /********** End 2 **********/
}

status AddList(LISTS &Lists, char ListName[])  //case 14
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    int i = 0;
    Lists.elem[Lists.length].L = (LinkList) malloc(sizeof(LNode));
    Lists.elem[Lists.length].L->next = NULL;
    if (!Lists.elem[Lists.length].L)
        return OVERFLOW;
    while (ListName[i] != '\0') {
        Lists.elem[Lists.length].name[i] = ListName[i];
        i++;
    }
    Lists.elem[Lists.length].name[i] = '\0';
    Lists.length++;
    return OK;
}

status RemoveList(LISTS &Lists, char ListName[])  //case 15
// Lists中删除一个名称为ListName的线性表
{
    int i,n;
    for (i = 0; i < Lists.length; i++) {
        int j = strcmp(Lists.elem[i].name, ListName);
        if (j == 0) { //匹对陈功执行删除操作
            for(n=i;n<Lists.length-1;n++)
                Lists.elem[i] = Lists.elem[i + 1];
            break;
        }
    }
    if (i == Lists.length) return ERROR;
    Lists.length--;
    return OK;
    /********** End **********/
}

int LocateList(LISTS Lists, char ListName[]) //case 16
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    int i;
    for (i = 1; i <= Lists.length; i++) {
        int j = strcmp(Lists.elem[i - 1].name, ListName);
        if (j == 0)
            return i;
    }
    return ERROR;
}
