#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int KeyType;
typedef struct {
    KeyType key;   //整型
    char others[20];   //字符型
} TElemType; //二叉树结点类型定义

typedef struct BiTNode {  //二叉链表结点的定义
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct {
    struct {
        char name[30];
        BiTree T;
    } elem[100];
    int length;
    int listsize;
} wood;

void visit(BiTree T) {
    printf(" %d,%s", T->data.key, T->data.others);
}

//函数声明
status CreateBiTree(BiTree &T, TElemType definition[]);

status ClearBiTree(BiTree &T);

status TreeEmpty(BiTree &T);

int BiTreeDepth(BiTree T);

BiTNode *LocateNode(BiTree T, KeyType e);

status Assign(BiTree &T, KeyType e, TElemType value);

BiTNode *GetSibling(BiTree T, KeyType e);

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);

status DeleteNode(BiTree &T, KeyType e);

//三种排序至少有一种试非递归的
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));

status InOrderTraverse(BiTree T,void (*visit)(BiTree));

status PostOrderTraverse(BiTree T, void (*visit)(BiTree));

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));

status SaveBiTree(BiTree T, char FileName[]);

status LoadBiTree(BiTree &T, char FileName[]);

status Addtrees(wood Trees, char name[]);

status TreesTraverse(wood trees,void(*visit)(BiTree));

status DestroyBiTree(BiTree &T);

status RemoveTree(wood Trees, char name[]);

int main(void) {
    wood Trees;  //森林
    Trees.length = 0;
    BiTree T,node=NULL;  //根节点与节点
    TElemType definition[100];  //节点数据数组
    TElemType e;
    int key;  //节点的关键字
    int en;
    int LR;
    int n;
    int opt = 0;
    char name[30];
    char FileName[30];
    int op = 1;
    int j;
    int f,i,p;
    int ans;
    int count = 0;
    int flag;
    T = NULL; //表L置为空
    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. 添加二叉树      9. 删除节点\n");
        printf("    	  2. 清空二叉树      10. 前序遍历\n");
        printf("    	  3. 判空二叉树      11. 中序遍历\n");
        printf("    	  4. 二叉树深度      12. 后序遍历\n");
        printf("    	  5. 查找结点       13. 层序遍历\n");
        printf("    	  6. 节点赋值       14. 保存二叉树\n");
        printf("    	  7. 获得兄弟节点    15. 加载二叉树\n");
        printf("    	  8. 插入节点       16. 销毁二叉树\n");
        printf("    	  17.遍历森林        0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~17]:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("请输入要添加的二叉树的个数");
                scanf("%d", &n);
                while (n--) {
                    printf("请输入要添加的二叉树的名称\n");
                    scanf("%s", name);
                    Addtrees(Trees, name);  //增加函数的使用
                    printf("二叉树添加成功,请输入节点，要求带有关键字和字符，以-1 null结束\n");
                    i = 0;
                    do {
                        scanf("%d%s",&definition[i].key,definition[i].others);
                    } while (definition[i++].key!=-1);\
                    ans=CreateBiTree(Trees.elem[Trees.length-1].T,definition);
                }
                TreesTraverse(Trees,visit);
                printf("\n");
                getchar();
                printf("\n");
                break;
            case 2:  // 清空线性表 done
                printf("请输入你想要清空的二叉树的名字");
                scanf("%s", name);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行删除操作
                        flag = ClearBiTree(Trees.elem[i].T);
                        if (flag == ERROR) printf("该二叉树已经为空！");
                        if (flag == OK) printf("已清空该二叉树");
                        if (flag == INFEASIBLE) printf("ERROR");
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 3: //判断是否为空 done
                printf("请输入二叉树的名字");
                scanf("%s", name);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行删除操作
                        flag = TreeEmpty(Trees.elem[i].T);
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
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行删除操作
                        flag = BiTreeDepth(Trees.elem[i].T);
                        printf("此二叉树的深度为：%d", flag);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 5:  //查找元素 done
                printf("请输入要进行查找节点线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行删除操作
                        printf("请输入要查找的元素的位置");
                        scanf("%d", &p);
                        node = LocateNode(Trees.elem[i].T,key);  //查找函数的使用
                        if (node) printf("获取元素成功!关键字%d的节点是%s", key, node->data.others);
                        if (node) printf("ERROR");
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 6: //节点赋值 done
                printf("请输入要进行操作的二叉树名字");
                scanf("%s", name);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行查找操作
                        scanf("%d%d%s",&key,&e.key,e.others);
                        ans=Assign(Trees.elem[i].T,key,e);
                        if (ans == ERROR) printf("ERROR");
                        else{
                            printf("赋值成功!");
                            PreOrderTraverse(Trees.elem[i].T,visit);
                        }
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 7: //获得兄弟节点 done
                printf("请输入要进行操作的二叉树名字");
                scanf("%s", name);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行查找操作
                        printf("请输入要查找前驱的元素");
                        scanf("%d", &en);
                        node = GetSibling(Trees.elem[i].T,en);  //查找函数的使用
                        if(node) printf("%d,%s",node->data.key,node->data.others);
                        else printf("ERROR");
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 8:  //插入节点 done
                printf("请输入要进行查找后继元素线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行查找操作
                        scanf("%d%d%d%s",&en,&LR,&e.key,e.others);
                        ans=InsertNode(T,en,LR,e);
                        if (ans==OK)
                        {
                            PreOrderTraverse(Trees.elem[i].T,visit);
                            printf("\n");
                            InOrderTraverse(Trees.elem[i].T,visit);
                        }
                        else printf("ERROR");
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 9:  //删除元素  done
                printf("请输入要进行插入元素线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行查找操作
                        scanf("%d",&en);
                        ans=DeleteNode(Trees.elem[i].T,en);
                        if (ans==OK)
                        {
                            PreOrderTraverse(Trees.elem[i].T,visit);
                            printf("\n");
                            InOrderTraverse(Trees.elem[i].T,visit);
                        }
                        else printf("删除操作失败");
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 10:  //前序遍历 done
                printf("请输入要进行删除元素线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) { //匹对陈功执行查找操作
                        PreOrderTraverse(Trees.elem[i].T,visit);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 11:  //中序遍历操作 done
                printf("请输入要进行遍历线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) {
                        InOrderTraverse(Trees.elem[i].T,visit);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 12:  //后序遍历操作 done
                printf("请输入要进行遍历线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) {
                        PostOrderTraverse(Trees.elem[i].T,visit);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 13:  //层序遍历操作 done
                printf("请输入要进行遍历线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) {
                        LevelOrderTraverse(T,visit);
                        break;
                    }
                }
                getchar();
                getchar();
                break;
            case 14:  //保存二叉树 done
                printf("请输入要保存的线性表的名字");
                scanf("%s", name);
                printf("请输入文件存储的地址");
                scanf("%s", FileName);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) {
                        j = SaveBiTree(Trees.elem[i].T, FileName);
                        printf("保存成功");
                        break;
                    }
                }
                if (i >= Trees.length) printf("没有相应的线性表");
                getchar();
                getchar();
                break;
            case 15: //加载二叉树
                printf("请输入要读取的文件地址");
                scanf("%s", FileName);
                printf("请输入要保存的线性表的名字");
                scanf("%s", name);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if (j == 0) {
                        DestroyBiTree(Trees.elem[i].T);
                        j = LoadBiTree(Trees.elem[i].T, FileName);
                        if (j == OK) printf("读取成功");
                    }
                    break;
                }
                //遍历检验
                getchar();
                getchar();
                break;
            case 16: //销毁二叉树
                printf("请输入要销毁的二叉树的名字");
                scanf("%s", name);
                for (i = 0; i < Trees.length; i++) {
                    j = strcmp(Trees.elem[i].name, name);
                    if(j==0){
                        DestroyBiTree(Trees.elem[i].T);
                        free(Trees.elem[i].name);
                        Trees.length--;
                        while(i<Trees.length){
                            Trees.elem[i]=Trees.elem[i+1];
                            i++;
                        }
                    }
                    printf("\n");
                }
                if (Trees.length == 0) printf("没有可供删除的二叉树");
                getchar();
                getchar();
                break;
            case 17:  //遍历多二叉树
                for(i=0;i<Trees.length;i++){
                    printf("%s\n",Trees.elem[i].name);
                    PreOrderTraverse(Trees.elem[i].T,visit);
                    InOrderTraverse(Trees.elem[i].T,visit);
                    printf("\n");
                }
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

status CreateBiTree(BiTree &T, TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int flag;
    T = (BiTree) malloc(sizeof(BiTNode));
    static int i = 0, count = definition[0].key;
    i++;
    if (definition[i - 1].key == 0) T = NULL;
    else if (definition[i - 1].key != 0) {
        if (count != definition[i - 1].key) return ERROR;
        T->data.key = definition[i - 1].key;
        strcpy(T->data.others, definition[i - 1].others);
        count++;
        flag = CreateBiTree(T->lchild, definition);
        flag = CreateBiTree(T->rchild, definition);
        if (flag == ERROR) return ERROR;
    }
    return OK;
    /********** End **********/
}

status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T) {
        ClearBiTree(T->lchild);
        ClearBiTree(T->rchild);
        free(T);
        T = NULL;
    }
    return OK;
    /********** End **********/
}

int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!T) return ERROR;
    int L_d = BiTreeDepth(T->lchild);
    int R_d = BiTreeDepth(T->rchild);
    return (((L_d > R_d) ? L_d : R_d) + 1);
    /********** End **********/
}

BiTNode *LocateNode(BiTree T, KeyType e)
//查找结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTree n_tree = NULL;
    if (T) {
        if (e == T->data.key) {
            n_tree = T;
            return n_tree;
        }
        n_tree = LocateNode(T->lchild, e);
        n_tree = LocateNode(T->rchild, e);
    }
    return n_tree;
    /********** End **********/
}

status Assign(BiTree &T, KeyType e, TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTree t = (BiTree) malloc(sizeof(BiTNode));
    BiTree ot = t;
    if (e > value.key) {
        ot = LocateNode(T, value.key);
        if (ot) return ERROR;
    }
    t = LocateNode(T, e);
    if (!t) return ERROR;
    t->data = value;
    return OK;
    /********** End **********/
}

BiTNode *GetSibling(BiTree T, KeyType e)
//实现获得兄弟结点
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /*
     * 遍历 找到之后
     * 父节点的左右节点
     */
    //非递归中序遍历 实现 栈
    BiTree stack[100];
    int top = 0;
    BiTree t = T;
    while (t != NULL || top > 0) {
        while (t != NULL) {
            stack[top++] = t;
            t = t->lchild;
        }
        t = stack[--top];
        if (t->lchild && t->lchild->data.key == e && t->rchild) return t->rchild;
        if (t->rchild && t->rchild->data.key == e && t->lchild) return t->lchild;
        t = t->rchild;
    }
    return ERROR;
    /********** End **********/
}

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTree new_node = (BiTree) malloc(sizeof(BiTNode)), node;
    new_node->data = c;
    if (LR == -1) {
        new_node->rchild = T;
        new_node->lchild = NULL;
        T = new_node;
        return OK;
    }
    /*
     * LR 0 T 1R -1 ROOT
     * e->lr==c->r
     * e是序号
     * c是数据
     */
    /*
     * 查找节点
     * 插入
     */
    BiTree stack[100];
    int top = 0;
    node = T;
    while (node != NULL || top > 0) {
        while (node != NULL) {
            stack[top++] = node;
            node = node->lchild;
        }
        node = stack[--top];
        if (node->data.key == c.key) return ERROR;
        if (node->data.key == e && node) {
            if (LR == 0) {
                new_node->rchild = node->lchild;
                new_node->lchild = NULL;
                node->lchild = new_node;
            } else {
                new_node->rchild = node->rchild;
                new_node->lchild = NULL;
                node->rchild = new_node;
            }
            return OK;
        }
        node = node->rchild;
    }
    return ERROR;
    /********** End **********/
}

status DeleteNode(BiTree &T, KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //删除头节点
    //查找父节点
    //删除节点
    //释放内存
    //删除情况分类：
    /*
     * 同时，如果关键字为e的结点度为0，删除即可；
     * 如关键字为e的结点度为1，用关键字为e的结点孩子代替被删除的e位置；
     * 如关键字为e的结点度为2，用e的左孩子代替被删除的e位置，e的右子树作为e的左子树中最右结点的右子树。
     */
    BiTree node, old_node, cur_node;
    BiTree stack[100];
    int top = 0;
    node = T;
    int flag = 0;
    while (node != NULL || top > 0) {
        while (node != NULL) {
            stack[top++] = node;
            node = node->lchild;
        }
        node = stack[--top];
        //考虑根节点的情况
        if (node->data.key == e && top == 0) {
            old_node = node;
            node = node->lchild;
            cur_node = node;
            while (cur_node->rchild) cur_node = cur_node->rchild;
            cur_node->rchild = old_node->rchild;
            free(old_node);
            old_node = NULL;
            T = node;
            return OK;
        }
        //考虑子树的情况
        //查找父节点成功 执行删除操作
        if ((node->lchild && node->lchild->data.key == e) || node->rchild && node->rchild->data.key == e) {
            //为左子树
            if (node->lchild && node->lchild->data.key == e) {
                cur_node = node->lchild;
                //度为0
                if (!(cur_node->lchild || cur_node->rchild)) {
                    free(cur_node);
                    node->lchild = NULL;
                    flag = 1;
                }
                    //度为2
                else if (cur_node->lchild && cur_node->rchild) {
                    old_node = cur_node;
                    node->lchild = cur_node->lchild;
                    while (cur_node->rchild) cur_node = cur_node->rchild;
                    cur_node->rchild = old_node->rchild;
                    free(old_node);
                    old_node = NULL;
                    flag = 1;
                }
                    //度为1
                else {
                    if (cur_node->lchild) {
                        old_node = cur_node;
                        node->lchild = cur_node->lchild;   //两个if语句可以使用 ?: 代替
                        free(old_node);
                    } else {
                        old_node = cur_node;
                        node->lchild = cur_node->rchild;
                        free(old_node);
                    }
                    flag = 1;
                }
                return OK;
            }
            //为右子树
            if (node->rchild) {
                cur_node = node->rchild;
                //度为0
                if (!(cur_node->lchild && cur_node->rchild)) {
                    free(cur_node);
                    node->rchild = NULL;
                    flag = 1;
                }
                    //度为2
                else if (cur_node->lchild && cur_node->rchild) {
                    old_node = cur_node;
                    node->rchild = cur_node->lchild;
                    while (cur_node->rchild) cur_node = cur_node->rchild;
                    cur_node->rchild = old_node->rchild;
                    free(old_node);
                    old_node = NULL;
                    flag = 1;
                }
                    //度为1
                else {
                    if (cur_node->lchild) {
                        old_node = cur_node;
                        node->rchild = cur_node->lchild;   //两个if语句可以使用 ?: 代替
                        free(old_node);
                    } else {
                        old_node = cur_node;
                        node->rchild = cur_node->lchild;
                        free(old_node);
                    }
                    flag = 1;
                }
                return OK;
            }
        }
        if (flag == 1) return OK;
        node = node->rchild;
    }
    return ERROR;
    /********** End **********/
}

status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
//先序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T) {
        visit(T);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
    return OK;
    /********** End **********/
}

status InOrderTraverse(BiTree T, void (*visit)(BiTree))
//中序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //非递归
    BiTree node;
    BiTree stack[100];
    int top = 0;
    node = T;
    while (node != NULL || top > 0) {
        while (node != NULL) {
            stack[top++] = node;
            node = node->lchild;
        }
        node = stack[--top];
        visit(node);
        node = node->rchild;
    }
    return OK;

    //递归
    /*
        if (T) {
            InOrderTraverse(T->lchild, visit);
            visit(T);
            InOrderTraverse(T->rchild, visit);
        }
        return OK;
     */
    /********** End **********/
}

status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
//后序遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T) {
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T);
    }
    return OK;
    /********** End **********/
}

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
//按层遍历二叉树T
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //队列先进先出
    //出的时候将其左右孩子放入队尾
    BiTree node;
    BiTree queue[100];
    int in = 0;
    int out = 0;
    queue[in++] = T;
    while (in > out) {
        if (queue[out]) {
            visit(queue[out]);
            queue[in++] = queue[out]->lchild;
            queue[in++] = queue[out]->rchild;
        }
        out++;
    }
    /********** End **********/
}

status RecurSave(BiTree T, FILE *fp) {
    BiTree b_node;  //空白节点
    char b[] = "null";
    b_node = (BiTree) malloc(sizeof(BiTNode));
    b_node->data.key = 0;
    strcpy(b_node->data.others, b);
    if (T) {
        fwrite(&T->data, sizeof(TElemType), 1, fp);
        if (RecurSave(T->lchild, fp))
            if (RecurSave(T->rchild, fp))
                return OK;
            else
                return ERROR;
    } else {
        fwrite(&b_node->data, sizeof(TElemType), 1, fp);
        return OK;
    }
}

status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    FILE *fp;
    fp = fopen(FileName, "wb");
    if (fp == NULL)
        return ERROR;
    if (RecurSave(T, fp) == OK) {
        fclose(fp);
        return OK;
    } else {
        fclose(fp);
        return ERROR;
    }

    /********** End 1 **********/
}

status LoadBiTree(BiTree &T, char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    FILE *fp;
    TElemType d[100];
    int i = 0;
    int s;
    fp = fopen(FileName, "rb");
    if (fp == NULL)
        return ERROR;
    else {
        while (fread(&d[i], sizeof(TElemType), 1, fp)) i++;
        s = CreateBiTree(T, d);
        if (s) return OK;
        return ERROR;
    }
    /********** End 2 **********/
}

status AddList(wood &Trees, char TreeName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    int i = 0;
    Trees.elem[Trees.length].T = (BiTree) malloc(sizeof(BiTNode));
    Trees.elem[Trees.length].T->rchild = NULL;
    Trees.elem[Trees.length].T->lchild=NULL;
    if (!Trees.elem[Trees.length].T)
        return OVERFLOW;
    strcpy(Trees.elem[Trees.length].name,TreeName);
    while (TreeName[i] != '\0') {
        Trees.elem[Trees.length].name[i] = TreeName[i];
        i++;
    }
    Trees.elem[Trees.length].name[i] = '\0';
    Trees.length++;
    return OK;
}

status TreesTraverse(wood trees){
    int i;
    for(i=0;i<trees.length;i++){
        PreOrderTraverse(trees.elem[i].T,visit);
    }
    return OK;
}

status DestroyBiTree(BiTree &T)
{
    if (T)
    {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free(T);
        T=NULL;
    }
    return OK;
}
