#include <stdio.h>
#include <stdlib.h>

typedef struct element
{
    int freq;

    int value;
    struct element *left;
    struct element *right;

} Tree;


typedef struct priorityQ
{
    Tree *elem;
    struct priorityQ *next;
} PriorityQ;


PriorityQ* CountFreq(FILE *fin, PriorityQ *head);
Tree *merge(Tree *l, Tree *r);
PriorityQ *insertElem(PriorityQ *head, Tree *elem);
Tree *buidHuffmanTree(PriorityQ *head);
void make_code(Tree* tree,char *codeSym,int *index, char **codeBuf);
void WriteBit(FILE* fin, char *byte, int *pos, int bit);
void ReadBit(char** symBuff, char *byte, int *pos, FILE* fin,FILE* fout);



Tree *reconstruc_tree(Tree *tree, unsigned char *block, char *shift, FILE *fin);
void decoder(Tree *tree, unsigned char *block, char *shift, FILE *fin, FILE *fout);

void writeTree(FILE* fin, Tree* tree, char *byte, int *pos);
void encodeFile(FILE* fin, FILE* fout, char *byte, int *pos, char **codeBuf);


Tree *merge(Tree *l, Tree *r)
{

    Tree *nf = (Tree*)malloc(sizeof(Tree));
    nf->freq = l->freq + r->freq;
    nf->left = l;
    nf->right = r;

    nf->value = -1;
    return nf;
}




PriorityQ* CountFreq(FILE* fin, PriorityQ* head)   // частота
{

    int c;
    int i;
    unsigned char amount[2048]= {0};
    int count;
    while (!feof(fin))
    {
        c = fgetc(fin);
        if (c!=EOF)
        {
            amount[c]++;
            count++;
        }
    }

    for(i=0; i<256; i++)
    {

        if(amount[i] > 0)
        {

            Tree *new_node = (Tree *) malloc(sizeof(Tree));

            new_node->freq = amount[i];
            new_node->value = i;



            new_node->left = NULL;
            new_node->right = NULL;

            head = insertElem(head, new_node);
        }

    }
    return head;
};




PriorityQ *insertElem(PriorityQ *head, Tree *elem)   // вставка в очередь
{

    PriorityQ *newElem = (PriorityQ*)malloc(sizeof(PriorityQ));
    newElem->elem = elem;
    newElem->next = NULL;

    if (head == NULL) return newElem;
    PriorityQ *first, *second;
    first = head;
    second = head->next;


    if (newElem->elem->freq < first->elem->freq)
    {
        newElem->next = first;
        return newElem;
    }
    else while (second)
        {
            if (newElem->elem->freq < second->elem->freq)
            {
                newElem->next = second;
                first->next = newElem;
                return head;
            }

            first = second;
            second = second->next;
        }

    first->next = newElem;
    return head;
}



Tree *BuidHuffmanTree(PriorityQ *head)    // дерево
{
    PriorityQ *tmp;
    PriorityQ *newHead;
    PriorityQ *first = NULL;
    PriorityQ *second = NULL;
    tmp = head;
    Tree *buf;

    while (tmp->next != NULL)
    {
        newHead = (tmp->next)->next;
        first = tmp;
        second = tmp->next;
        buf = merge(first->elem, second->elem);
        tmp = insertElem(newHead, buf);
        free(first);
        free(second);
    }

    buf = tmp->elem;
    free(tmp);
    return buf;
}



void make_code(Tree* tree,char *codeSym,int *index, char **codeBuf)
{
    if (!tree) return;


    if (tree->left->value == -1)
    {
        codeSym[*index] = '0';
        (*index)++;


        make_code(tree->left, codeSym, index, codeBuf);
    }


    else
    {
        codeSym[*index] = '0';

        int y = 0;
        while (codeSym[y] != '\0')
        {
            codeBuf[tree->left->value][y] = codeSym[y];
            y++;
        }
    }


    if (tree->right->value == -1)
    {
        codeSym[*index] = '1';
        (*index)++;

        make_code(tree->left, codeSym, index, codeBuf);

    }
    else
    {
        codeSym[*index] = '1';
        int y = 0;
        while (codeSym[y] != '\0')
        {
            codeBuf[tree->right->value][y] = codeSym[y];
            y++;
        }



        codeSym[*index] = '\0';
        (*index)--;
    }
return;
}



void WriteBit(FILE* fin, char *byte, int *pos, int bit)
{


    if(bit == 0)
    {
        (*pos)++;
    }

    if(bit == 1)
    {
        *byte = (*byte) | (1 << (7-(*pos)));
        (*pos)++;
    }

    if (*pos == 8){

        fwrite(&byte, 1, 1, fout);
        *pos = 0;
        *byte = 0;
    }

}


/*void ReadBit(char** codeBuf, char *byte, int *pos, FILE* fin,FILE* fout)
{
    if()
    {


    }


    if()
    {

    }

    if(*pos == 8)
    {
    fwrite(&byte, 1, 1, fout);

    *pos = 0;
    *byte = 0;
    }
}

*/


Tree* reconstruc_tree(Tree *tree, unsigned char *block, char *shift, FILE *fin)
{

    Tree *tmp = (Tree*)malloc(sizeof(Tree));
	tmp->freq = -1;
	tmp->left = NULL;
	tmp->right = NULL;

	tree = tmp;


	unsigned char c = (*block >> *shift) & 1;
	(*shift)--;
	if (c == 0) {
		tmp->value = -1;
		tmp->left = reconstruc_tree(tmp->left, block, shift, fin);
		tmp->right = reconstruc_tree(tmp->right, block, shift, fin);
		return tmp;
	}
	else {
		char symbol = 0;
		int i;
		for (i = 7; i >= 0; i--) {
			if (*shift < 0) {
				*block = fgetc(fin);
				*shift = 7;
			}
			symbol = symbol | (((*block >> *shift) & 1) << i);
			(*shift)--;
		}
		tmp->value = symbol;

		return tmp;
	}
	*block = fgetc(fin);

	return tmp;
}



void decoder(Tree *tree, unsigned char *block, char *shift, FILE *fin, FILE *fout) {



	int i, n;
	Tree *tmp = tree;
	n = 0;
    *block = fgetc(fin);
    *shift = 7;

	while (!feof(fin)) {

		if (!((tmp->left) && (tmp->right))) {
			fprintf(fout, "%c", tmp->value);
			tmp = tree;
			n++;
			if (n == countSym) return;
		}

		char branch = (*block >> *shift) & 1;
		(*shift)--;

        *block = fgetc(fin);
        *shift = 7;


		if (branch == '0')
			tmp = tmp->left;
		else  if (branch == '1')
			tmp = tmp->right;


	}
	return;
}




int main()
{
    FILE *fin = fopen("in.txt", "rb");
    FILE *fout = fopen("out.txt", "wb");

    unsigned char a;


    fscanf(fin, "%c\n", &a);


    char** codeBuf = (char**)malloc(sizeof(char*)*256);

    char codeSym[8] = {0}
    Tree *tree = NULL;
    countSym = 0;
    int index = 0;

    if (a=='c')
    {
        PriorityQ* head = NULL;
        head = CountFreq(fin, head);
        tree = BuidHuffmanTree(head);
        make_code(tree, codeSym, &index, codeBuf);

        fseek(fin, 3, SEEK_SET);

        fprintf(fout, "%d ", countSym);//записать для декодирования

        /* call function to write Tree into file */


        /* call function to write code */

        /*
        char pos = 0;
        char byte = 0;

        WriteBit(fin, &byte, &pos, bit);

        free(tree);


        int bit = 0;
        if (code_length % 8 == 0)
            bit = code_length / 8;
        else
            bit = code_length / 8 + 1;


        fseek(fin, 4, SEEK_SET);

        ReadBit(codeBuf, &byte, &pos, fin, fout);
        */
    }

    else if(a == 'd')
    {
       fscanf(fin, "%d ", &countSym);

	char shift = 7;
		int block = fgetc(fin);
		tree = reconstructTree(tree, &block, &shift, fin);
		decoder(tree, &block, &shift, fin, fout);


	}

	int i;
	int Symbol[256]= {0};

	for (i = 0; i < 256; i++)
		if (Symbol[i] > 0)
			free(codeBuf[i]);
	free(codeBuf);

	fclose(fin);
	fclose(fout);

}
