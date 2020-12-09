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
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
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
/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    /*
     * V--�ڵ���Ϣ
     * VR--�ڵ�֮��Ĺ�ϵ
     */
    int i = 0, k = 0, j;
    int pos_i, pos_j;
    int flag = 0, p = 0, q = 0;
    int num = 0;
    G.vexnum = 0;
    G.arcnum = 0;
    //ƥ��Ԫ���Ƿ��ظ����Լ�Ԫ���Ƿ�Ϸ��������Ƿ�Ϸ�
    do {
        q = p;
        while (V[++q].key != -1) {
            if (V[p].key == V[q].key) flag = 1;
        }
        num++;
    } while (V[++p].key != -1);
    if (num > MAX_VERTEX_NUM)
        return ERROR;
    //���������
    if (flag == 0) {
        do {
            G.vertices[i].data = V[i];
            G.vertices[i].firstarc = NULL;
            G.vexnum++;
        } while (V[++i].key != -1);
        //�����߱�
        while (VR[k][0] != -1) {
            i = VR[k][0];
            j = VR[k][1];
            pos_i = LocateVex(G, i);
            pos_j = LocateVex(G, j);
            if (pos_i==-1||pos_j==-1) return ERROR;
            if (!(pos_j < G.vexnum && pos_i < G.vexnum)) return ERROR;
            ArcNode *e = NULL;
            //����i��j�Ĺ�ϵ
            e = (ArcNode *) malloc(sizeof(ArcNode));
            e->adjvex = pos_j;
            e->nextarc = G.vertices[pos_i].firstarc;
            G.vertices[pos_i].firstarc = e;
            //����j��i�Ĺ�ϵ
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
/*��������ͼG*/
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int i;
    VertexType *vp;
    ArcNode *p, *q;
    ALGraph *g = &G;
    if (!g) return ERROR;
    //���ͷű�
    for (i = 0; i < G.vexnum; i++) {
        p = G.vertices[i].firstarc;
        while (p) {
            q = p->nextarc;
            free(p);
            p = q;
        }
    }
    //���ͷŶ���,ͼ����Ϣ,������Ŀ,����Ŀ,kind��Ϊ0
    G.vexnum = 0;
    G.arcnum = 0;
    G.kind = UNKOWN;
    return OK;
    /********** End **********/
}

status PutVex(ALGraph &G, KeyType u, VertexType value)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int pos,flag;
    //�ж��޸�λ���Ƿ����
    if (LocateVex(G, u) == -1) return ERROR;
    flag=LocateVex(G, value.key);
    //�ж��Ƿ��ظ�
    if (u != value.key && flag != -1) return ERROR;
    //����Ϸ�ִ�и�ֵ����
    //��λu
    pos = LocateVex(G, u);
    G.vertices[pos].data = value;
    return OK;
    /********** End **********/
}

int FirstAdjVex(ALGraph G, KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int pos;
    pos = LocateVex(G, u);
    if (pos == -1) return -1;
    if (!G.vertices[pos].firstarc) return -1;
    return G.vertices[pos].firstarc->adjvex;
    /********** End **********/
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int pos;
    ArcNode *wp;
    pos = LocateVex(G, v);
    //�Ҳ���v return ERROR
    //v�ĺ���û�л� ���ش�����Ϣ
    if (pos == -1) return -1;
    if (!G.vertices[pos].firstarc) return -1;
    //����w
    wp = G.vertices[pos].firstarc;
    while (G.vertices[wp->adjvex].data.key != w) {
        wp = wp->nextarc;
        if (wp->nextarc == NULL) return -1;  //�Ҳ���w
    }
    return wp->nextarc->adjvex;
    /********** End **********/
}

status InsertVex(ALGraph &G, VertexType v)
//��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    //�жϲ���λ���Ƿ�Ϸ�
    if (G.vexnum >= MAX_VERTEX_NUM) return ERROR;
    //�жϲ���֮���Ƿ��ظ�
    if (LocateVex(G, v.key) != -1) return ERROR;
    //��ʼ�������
    G.vexnum++;
    G.vertices[G.vexnum - 1].data = v;
    G.vertices[G.vexnum - 1].firstarc = NULL;
    return OK;
    /********** End **********/
}

status DeleteVex(ALGraph &G, KeyType v)
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    //�ж�ɾ���Ĺؼ����Ƿ�Ϸ�
    if (LocateVex(G, v) == -1) return ERROR;
    if (LocateVex(G, v) != -1) {
        //ɾ��֮����Ȼ��ͼ
        if (G.vexnum == 1) return ERROR;
        //�ؼ��ֺϷ���ִ��ɾ������
        int i, pos_v;
        ArcNode *vp, *iptr, *cur;
        pos_v = LocateVex(G, v);
        vp = G.vertices[pos_v].firstarc;
        //ɾ��vp��Ӧ������
        while (vp) {
            cur = vp;
            vp = vp->nextarc;
            free(cur);
            G.arcnum--;
        }
        G.vexnum--;
        for (i = pos_v; i < G.vexnum; i++)
            G.vertices[i] = G.vertices[i + 1];  //ɾ��֮�����������
        //����ɾ��֮����ڽӱ�����vɾ������������v��-1
        for (i = 0; i < G.vexnum; i++) {
            iptr = G.vertices[i].firstarc;
            while (iptr) {
                //�������pos_v ִ��ɾ�����Ĳ���
                if (iptr->adjvex == pos_v) {
                    if (iptr == G.vertices[i].firstarc) {
                        //����ǵ�һ��Ԫ��
                        G.vertices[i].firstarc = iptr->nextarc;
                        free(iptr);
                        iptr = G.vertices[i].firstarc;
                    } else {
                        //������ǵ�һ��Ԫ��
                        cur->nextarc = iptr->nextarc;
                        free(iptr);
                        iptr = cur->nextarc;
                    }
                } else {
                    //�������pos_v����ż�һ
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
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    //�ײ巨
    //�жϲ���λ���Ƿ�Ϸ�
    int pos_v, pos_w;
    pos_v = LocateVex(G, v);
    pos_w = LocateVex(G, w);
    if (pos_v == -1 || pos_w == -1) return ERROR; //�������Ҳ���
    //������Ѿ��ظ� ����ERROR
    ArcNode *vp, *wp, *cur;
    vp = G.vertices[pos_v].firstarc;
    wp = G.vertices[pos_w].firstarc;
    //��v�����Ƿ���w
    while (vp) {
        if (vp->adjvex == pos_w) return ERROR;
        vp = vp->nextarc;
    }
    vp = G.vertices[pos_v].firstarc;
    //���û��wִ�в������
    //��v����ͷ��w
    ArcNode *New_Arc1 = (ArcNode *) malloc(sizeof(ArcNode));
    New_Arc1->adjvex = pos_w;
    cur = vp;
    New_Arc1->nextarc = cur;
    G.vertices[pos_v].firstarc = New_Arc1;
    //��w����ͷ��v
    ArcNode *New_Arc2 = (ArcNode *) malloc(sizeof(ArcNode));
    New_Arc2->adjvex = pos_v;
    cur = wp;
    New_Arc2->nextarc = cur;
    G.vertices[pos_w].firstarc = New_Arc2;
    //�������
    G.arcnum++;
    return OK;
    /********** End **********/
}

status DeleteArc(ALGraph &G, KeyType v, KeyType w)
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int flag = 0;
    int pos_v, pos_w;
    pos_v = LocateVex(G, v);
    pos_w = LocateVex(G, w);
    if (pos_v == -1 || pos_w == -1) return ERROR; //�������Ҳ���
    //����������� ����ERROR
    ArcNode *vp, *wp, *cur;
    vp = G.vertices[pos_v].firstarc;
    wp = G.vertices[pos_w].firstarc;
    //��v�����Ƿ���w ���û�� ����ERROR
    while (vp) {
        if (vp->adjvex == pos_w) {
            flag = 1;
            break;
        }
        vp = vp->nextarc;
    }
    vp = G.vertices[pos_v].firstarc;
    if (flag == 0) return ERROR;

    //���ж��Ϸ�ִ��ɾ�����Ĳ�����
    //��v����ɾ��w
    //���� w
    //�����һ������������ѭ��
    if (vp->adjvex == pos_w) {
        free(vp);
        G.vertices[pos_v].firstarc = NULL;
    } else {
        while (vp->nextarc->adjvex != pos_w)
            vp = vp->nextarc;
        cur = vp->nextarc;
        //����v��next
        vp->nextarc = cur->nextarc;
        free(cur);
    }
    //��w����ɾ��v
    //���� v
    //�����һ������������ѭ��
    if (wp->adjvex == pos_v) {
        free(wp);
        G.vertices[pos_w].firstarc = NULL;
    } else {
        while (wp->nextarc->adjvex != pos_v)
            wp = wp->nextarc;
        cur = wp->nextarc;
        //����w��next
        wp->nextarc = cur->nextarc;
        free(cur);
    }
    //ɾ�����
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
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    // �������ﲹ����룬��ɱ�������
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
//��ͼ������д�뵽�ļ�FileName��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 1 *********/
    int i, num;
    FILE *fp;
    ArcNode *cur;
    if ((fp = fopen(FileName, "wb")) == NULL) {
        printf("\t\t\t�����ļ�ʧ�ܣ�\n");
        return ERROR;
    }
    //�����ڽӱ�Ļ�����Ϣ
    fwrite(&G.kind, sizeof(int), 1, fp);  //�ڽӱ�����
    fwrite(&G.vexnum, sizeof(int), 1, fp); //������
    fwrite(&G.arcnum, sizeof(int), 1, fp); //����
    //����ÿһ����ŵĽڵ�ͻ�����Ϣ
    for (i = 0; i < G.vexnum; i++) {
        //����ÿ����ŵĶ�����Ϣ
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
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 2 *********/
    int i, k = 0, num;
    FILE *fp;
    ArcNode *cur,*nArc;
    if (G.vexnum != 0) return ERROR;
    if ((fp = fopen(FileName, "rb")) == NULL) {
        printf("\t\t\t�ļ�����ʧ�ܣ�\n");
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
        printf("��ͼΪ��");
        return OK;
    }
    printf("��ǰ�����¼���ͼ��\n");
    for (i = 0; i < ghs.length; i++) {
        //����ÿ��ͼ����Ϣ
        printf("\nͼ���ƣ�%s\n", ghs.elem[i].name);
        for (j = 0; j < ghs.elem[i].graph.vexnum; j++) {
            //�����ڽӱ�
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