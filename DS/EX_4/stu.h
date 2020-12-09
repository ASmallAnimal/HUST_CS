//
// Created by spiri on 2020/11/25.
//

#ifndef EX_4_STU_H
#define EX_4_STU_H

#endif //EX_4_STU_H

void Traverse(ALGraph G) {
    int i;
    for (i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        printf("%d %s", G.vertices[i].data.key, G.vertices[i].data.others);
        while (p) {
            printf(" %d", p->adjvex);
            p = p->nextarc;
        }
        printf("\n");
    }
}

void visit(VertexType v) {
    printf(" %d %s", v.key, v.others);
}

int LocateVex(ALGraph G, KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i, pos = 0;
    for (i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == u) {
            return pos;
        }
        pos++;
    }
    return -1;
    /********** End **********/
}

status AddGraphs(Graphs &ghs, char name[]) {
    strcpy(ghs.elem[ghs.length].name, name);
    ghs.length++;
    return OK;
}

status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /*
     * V--节点信息
     * VR--节点之间的关系
     */
    int i = 0, k = 0, j;
    int pos_i, pos_j;
    int flag = 0, p = 0, q = 0;
    int num = 0;
    G.vexnum = 0;
    G.arcnum = 0;
    //匹配元素是否重复，以及元素是否合法，容量是否合法
    do {
        q = p;
        while (V[++q].key != -1) {
            if (V[p].key == V[q].key) flag = 1;
        }
        num++;
    } while (V[++p].key != -1);
    if (num > MAX_VERTEX_NUM)
        return ERROR;
    //建立顶点表
    if (flag == 0) {
        do {
            G.vertices[i].data = V[i];
            G.vertices[i].firstarc = NULL;
            G.vexnum++;
        } while (V[++i].key != -1);
        //建立边表
        while (VR[k][0] != -1) {
            i = VR[k][0];
            j = VR[k][1];
            pos_i = LocateVex(G, i);
            pos_j = LocateVex(G, j);
            if (pos_i==-1||pos_j==-1) return ERROR;
            if (!(pos_j < G.vexnum && pos_i < G.vexnum)) return ERROR;
            ArcNode *e = NULL;
            //建立i与j的关系
            e = (ArcNode *) malloc(sizeof(ArcNode));
            e->adjvex = pos_j;
            e->nextarc = G.vertices[pos_i].firstarc;
            G.vertices[pos_i].firstarc = e;
            //建立j与i的关系
            e = (ArcNode *) malloc(sizeof(ArcNode));
            e->adjvex = pos_i;
            e->nextarc = G.vertices[pos_j].firstarc;
            G.vertices[pos_j].firstarc = e;
            G.arcnum++;
            k++;
        }
        return OK;
    }
    return ERROR;
    /********** End **********/
}

status DestroyGraph(ALGraph &G)
/*销毁无向图G*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i;
    VertexType *vp;
    ArcNode *p, *q;
    ALGraph *g = &G;
    if (!g) return ERROR;
    //先释放边
    for (i = 0; i < G.vexnum; i++) {
        p = G.vertices[i].firstarc;
        while (p) {
            q = p->nextarc;
            free(p);
            p = q;
        }
    }
    //再释放顶点,图的信息,顶点数目,边数目,kind置为0
    G.vexnum = 0;
    G.arcnum = 0;
    G.kind = UNKOWN;
    return OK;
    /********** End **********/
}

status PutVex(ALGraph &G, KeyType u, VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int pos,flag;
    //判断修改位置是否存在
    if (LocateVex(G, u) == -1) return ERROR;
    flag=LocateVex(G, value.key);
    //判断是否重复
    if (u != value.key && flag != -1) return ERROR;
    //如果合法执行赋值操作
    //定位u
    pos = LocateVex(G, u);
    G.vertices[pos].data = value;
    return OK;
    /********** End **********/
}

int FirstAdjVex(ALGraph G, KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int pos;
    pos = LocateVex(G, u);
    if (pos == -1) return -1;
    if (!G.vertices[pos].firstarc) return -1;
    return G.vertices[pos].firstarc->adjvex;
    /********** End **********/
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int pos;
    ArcNode *wp;
    pos = LocateVex(G, v);
    //找不到v return ERROR
    //v的后面没有弧 返回错误信息
    if (pos == -1) return -1;
    if (!G.vertices[pos].firstarc) return -1;
    //查找w
    wp = G.vertices[pos].firstarc;
    while (G.vertices[wp->adjvex].data.key != w) {
        wp = wp->nextarc;
        if (wp->nextarc == NULL) return -1;  //找不到w
    }
    return wp->nextarc->adjvex;
    /********** End **********/
}

status InsertVex(ALGraph &G, VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //判断插入位置是否合法
    if (G.vexnum >= MAX_VERTEX_NUM) return ERROR;
    //判断插入之后是否重复
    if (LocateVex(G, v.key) != -1) return ERROR;
    //开始插入操作
    G.vexnum++;
    G.vertices[G.vexnum - 1].data = v;
    G.vertices[G.vexnum - 1].firstarc = NULL;
    return OK;
    /********** End **********/
}

status DeleteVex(ALGraph &G, KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //判断删除的关键字是否合法
    if (LocateVex(G, v) == -1) return ERROR;
    if (LocateVex(G, v) != -1) {
        //删除之后仍然是图
        if (G.vexnum == 1) return ERROR;
        //关键字合法，执行删除操作
        int i, pos_v;
        ArcNode *vp, *iptr, *cur;
        pos_v = LocateVex(G, v);
        vp = G.vertices[pos_v].firstarc;
        //删除vp对应的数组
        while (vp) {
            cur = vp;
            vp = vp->nextarc;
            free(cur);
            G.arcnum--;
        }
        G.vexnum--;
        for (i = pos_v; i < G.vexnum; i++)
            G.vertices[i] = G.vertices[i + 1];  //删除之后的数组上移
        //遍历删除之后的邻接表，遇到v删除弧，遇到非v就-1
        for (i = 0; i < G.vexnum; i++) {
            iptr = G.vertices[i].firstarc;
            while (iptr) {
                //如果等于pos_v 执行删除弧的操作
                if (iptr->adjvex == pos_v) {
                    if (iptr == G.vertices[i].firstarc) {
                        //如果是第一个元素
                        G.vertices[i].firstarc = iptr->nextarc;
                        free(iptr);
                        iptr = G.vertices[i].firstarc;
                    } else {
                        //如果不是第一个元素
                        cur->nextarc = iptr->nextarc;
                        free(iptr);
                        iptr = cur->nextarc;
                    }
                } else {
                    //如果大于pos_v，序号减一
                    if (iptr->adjvex > pos_v)
                        iptr->adjvex--;
                    cur = iptr;
                    iptr = iptr->nextarc;
                }
            }
        }
    }
    return OK;
    /********** End **********/
}

status InsertArc(ALGraph &G, KeyType v, KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    //首插法
    //判断插入位置是否合法
    int pos_v, pos_w;
    pos_v = LocateVex(G, v);
    pos_w = LocateVex(G, w);
    if (pos_v == -1 || pos_w == -1) return ERROR; //弧顶点找不到
    //如果弧已经重复 返回ERROR
    ArcNode *vp, *wp, *cur;
    vp = G.vertices[pos_v].firstarc;
    wp = G.vertices[pos_w].firstarc;
    //找v后面是否有w
    while (vp) {
        if (vp->adjvex == pos_w) return ERROR;
        vp = vp->nextarc;
    }
    vp = G.vertices[pos_v].firstarc;
    //如果没有w执行插入操作
    //在v后面头插w
    ArcNode *New_Arc1 = (ArcNode *) malloc(sizeof(ArcNode));
    New_Arc1->adjvex = pos_w;
    cur = vp;
    New_Arc1->nextarc = cur;
    G.vertices[pos_v].firstarc = New_Arc1;
    //在w后面头插v
    ArcNode *New_Arc2 = (ArcNode *) malloc(sizeof(ArcNode));
    New_Arc2->adjvex = pos_v;
    cur = wp;
    New_Arc2->nextarc = cur;
    G.vertices[pos_w].firstarc = New_Arc2;
    //插入完成
    G.arcnum++;
    return OK;
    /********** End **********/
}

status DeleteArc(ALGraph &G, KeyType v, KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int flag = 0;
    int pos_v, pos_w;
    pos_v = LocateVex(G, v);
    pos_w = LocateVex(G, w);
    if (pos_v == -1 || pos_w == -1) return ERROR; //弧顶点找不到
    //如果弧不存在 返回ERROR
    ArcNode *vp, *wp, *cur;
    vp = G.vertices[pos_v].firstarc;
    wp = G.vertices[pos_w].firstarc;
    //找v后面是否有w 如果没有 返回ERROR
    while (vp) {
        if (vp->adjvex == pos_w) {
            flag = 1;
            break;
        }
        vp = vp->nextarc;
    }
    vp = G.vertices[pos_v].firstarc;
    if (flag == 0) return ERROR;

    //所有都合法执行删除弧的操作：
    //在v后面删除w
    //查找 w
    //如果第一个就是则不适用循环
    if (vp->adjvex == pos_w) {
        free(vp);
        G.vertices[pos_v].firstarc = NULL;
    } else {
        while (vp->nextarc->adjvex != pos_w)
            vp = vp->nextarc;
        cur = vp->nextarc;
        //链到v的next
        vp->nextarc = cur->nextarc;
        free(cur);
    }
    //在w后面删除v
    //查找 v
    //如果第一个就是则不适用循环
    if (wp->adjvex == pos_v) {
        free(wp);
        G.vertices[pos_w].firstarc = NULL;
    } else {
        while (wp->nextarc->adjvex != pos_v)
            wp = wp->nextarc;
        cur = wp->nextarc;
        //链到w的next
        wp->nextarc = cur->nextarc;
        free(cur);
    }
    //删除完成
    G.arcnum--;
    return OK;
    /********** End **********/
}

void DFS(ALGraph G, int i) {
    ArcNode *cur;
    visited[i] = TRUE;
    printf("%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
    cur = G.vertices[i].firstarc;
    while (cur) {
        if (!visited[cur->adjvex])
            DFS(G, cur->adjvex);
        cur = cur->nextarc;
    }
}

status DFSTraverse(ALGraph &G, void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = FALSE;
    for (i = 0; i < G.vexnum; i++)
        if (!visited[i])
            DFS(G, i);
    return OK;
    /********** End **********/
}

status InitQueue(Queue &Q) {
    Q.front = 0;
    Q.rear = 0;
    return OK;
}

status EnQueue(Queue &Q, int e) {
    if ((Q.rear + 1) % MAX_VERTEX_NUM == Q.front)
        return ERROR;
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAX_VERTEX_NUM;
    return OK;
}

status DeQueue(Queue &Q, int &e) {
    if (Q.front == Q.rear)
        return ERROR;
    e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAX_VERTEX_NUM;
    return OK;
}

status QueueEmpty(Queue &Q) {
    if (Q.rear == Q.front)
        return TRUE;
    else return ERROR;
}

status BFSTraverse(ALGraph &G, void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i;
    ArcNode *cur;
    Queue Q;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = FALSE;
    InitQueue(Q);
    for (i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            visited[i] = TRUE;
            visit(G.vertices[i].data);
            EnQueue(Q, i);
            while (!QueueEmpty(Q)) {
                DeQueue(Q, i);
                cur = G.vertices[i].firstarc;
                while (cur) {
                    if (!visited[cur->adjvex]) {
                        visited[cur->adjvex] = TRUE;
                        visit(G.vertices[cur->adjvex].data);
                        EnQueue(Q, cur->adjvex);
                    }
                    cur = cur->nextarc;
                }
            }
        }
    }
    return OK;
    /********** End **********/
}

int OutDegree(VNode i) {
    int num = 0;
    ArcNode *p;
    p = i.firstarc;
    while (p != NULL) {
        num++;
        p = p->nextarc;
    }
    return num;
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    int i, num;
    FILE *fp;
    ArcNode *cur;
    if ((fp = fopen(FileName, "wb")) == NULL) {
        printf("\t\t\t保存文件失败！\n");
        return ERROR;
    }
    //保存邻接表的基本信息
    fwrite(&G.kind, sizeof(int), 1, fp);  //邻接表类型
    fwrite(&G.vexnum, sizeof(int), 1, fp); //顶点数
    fwrite(&G.arcnum, sizeof(int), 1, fp); //弧数
    //保存每一个序号的节点和弧的信息
    for (i = 0; i < G.vexnum; i++) {
        //保存每个序号的顶点信息
        fwrite(&G.vertices[i].data, sizeof(VertexType), 1, fp);
        num = OutDegree(G.vertices[i]);
        fwrite(&num, sizeof(int), 1, fp);
        if ((cur = G.vertices[i].firstarc) != NULL) {
            fwrite(&cur->adjvex, sizeof(int), 1, fp);
            while ((cur = cur->nextarc) != NULL) {
                fwrite(&(cur->adjvex), sizeof(int), 1, fp);
            }
        }
    }
    fclose(fp);
    return OK;
    /********** End 1 **********/
}

status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    int i, k = 0, num;
    FILE *fp;
    ArcNode *cur,*nArc;
    if (G.vexnum != 0) return ERROR;
    if ((fp = fopen(FileName, "rb")) == NULL) {
        printf("\t\t\t文件加载失败！\n");
        return ERROR;
    }
    fread(&G.kind, sizeof(int), 1, fp);
    fread(&G.vexnum, sizeof(int), 1, fp);
    fread(&G.arcnum, sizeof(int), 1, fp);
    while (fread(&G.vertices[k].data, sizeof(VertexType), 1, fp)) {
        fread(&num, sizeof(int), 1, fp);
        if (num == 0)
            G.vertices[k].firstarc = NULL;
        else {
            nArc = (ArcNode *) malloc(sizeof(ArcNode));
            fread(&(nArc->adjvex), sizeof(int), 1, fp);
            G.vertices[k].firstarc=nArc;
            cur=nArc;
            for (i = 0; i < num-1; i++) {
                nArc = (ArcNode *) malloc(sizeof(ArcNode));
                fread(&(nArc->adjvex), sizeof(int), 1, fp);
                cur->nextarc = nArc;
                cur=nArc;
            }
            cur->nextarc=NULL;
        }
        k++;
    }
    fclose(fp);
    return OK;
    /********** End 2 **********/
}

status GraphsTraverse(Graphs &ghs) {
    int i, j;
    if (ghs.length == 0){
        printf("多图为空");
        return OK;
    }
    printf("当前有以下几个图：\n");
    for (i = 0; i < ghs.length; i++) {
        //遍历每个图的信息
        printf("\n图名称：%s\n", ghs.elem[i].name);
        for (j = 0; j < ghs.elem[i].graph.vexnum; j++) {
            //遍历邻接表
            ArcNode *p = ghs.elem[i].graph.vertices[j].firstarc;
            printf("%d %s", ghs.elem[i].graph.vertices[j].data.key, ghs.elem[i].graph.vertices[j].data.others);
            while (p) {
                printf(" %d", p->adjvex);
                p = p->nextarc;
            }
            printf("\n");
        }
    }
    return OK;
}