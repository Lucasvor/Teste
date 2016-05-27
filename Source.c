#pragma warning(disable : 4996)
#include <stdio.h>

typedef struct ArvoreRBN {
	int num;
	char cor;
	struct ArvoreRBN *esq, *dir, *par;
}Arvore;

Arvore *root = NULL;

/*
void esqRotate(Arvore *x) {
	Arvore *y;
	y = x->dir;  //Set y
	x->dir = y->esq; // Turn y's esq subtree into x's dir subtree
	if (y->esq != NULL) {
		y->esq->par = x; //Bridge the y's esq sublink
	}
	y->par = x->par; //Bridge x's old par and y's par
	if (x->par == NULL) {
		root = y;
	}
	else if (x->num == x->par->esq->num) {
		x->par->esq = y; //Bridge x's old par's esq or dir child
	}
	else x->par->dir = y;
	y->esq = x; //put x on y's esq
	x->par = y; //Take care of x's par

	return;
}*/
void esqRotate(Arvore *x) {
	Arvore *y;
	y = x->dir;
	x->dir = y->esq;
	if (y->esq != NULL)
		y->esq->par = x;
	y->par = x->par;
	if (x->par == NULL)
		root = y;
	else if ((x->par->esq != NULL) && (x->num == x->par->esq->num))
		x->par->esq = y;
	else
		x->par->dir = y;
	y->esq = x;
	x->par = y;
	return;
}

void dirRotate(Arvore *y) {
	Arvore *x;
	x = y->esq;
	y->esq = x->dir;

	if (x->dir != NULL)
		x->dir->par = y;
	x->par = y->par;
	if (y->par == NULL)
		root = x;
	else if ((y->par->esq != NULL) && (y->num == y->par->esq->num))
		y->par->esq = x;
	else
		y->par->dir = x;
	x->dir = y;
	y->par = x;

	return;
}
/*
void insereCor(Arvore *z) {
	Arvore *y = NULL;
	while (z->par->cor == 'r') {
		if (z->par->num == z->par->par->esq->num) {
			y = z->par->par->dir;
			if (y->cor == 'r') {
				z->par->cor = 'b';
				y->cor = 'b';
				z->par->par->cor = 'r';
				z = z->par->par;
			}
			else if (z->num == z->par->dir->num) {
				z = z->par;
				esqRotate(z);
			}
			z->par->cor = 'b';
			z->par->par->cor = 'r';
			dirRotate(z->par->par);
		}
		else {
			y = z->par->par->esq;
			if (y->cor == 'r') {
				z->par->cor = 'b';
				y->cor = 'b';
				z->par->par->cor = 'r';
				z = z->par->par;
			}
			else if (z->num == z->par->esq->num) {
				z = z->par;
				dirRotate(z);
			}
			z->par->cor = 'b';
			z->par->par->cor = 'r';
			esqRotate(z->par->par);
		}
	}
	root->cor = 'b';
}
*/
void insereCor(Arvore *z) {
	Arvore *y = NULL;
	while ((z->par != NULL) && (z->par->cor == 'r')) {
		if ((z->par->par->esq != NULL) && (z->par->num == z->par->par->esq->num)) {
			if (z->par->par->dir != NULL)
				y = z->par->par->dir;
			if ((y != NULL) && (y->cor == 'r')) {
				z->par->cor = 'b';
				y->cor = 'b';
				z->par->par->cor = 'r';
				if (z->par->par != NULL)
					z = z->par->par;
			}
			else {
				if ((z->par->dir != NULL) && (z->num == z->par->dir->num)) {
					z = z->par;
					esqRotate(z);
				}
				z->par->cor = 'b';
				z->par->par->cor = 'r';
				dirRotate(z->par->par);
			}
		}
		else {
			if (z->par->par->esq != NULL)
				y = z->par->par->esq;
			if ((y != NULL) && (y->cor == 'r')) {
				z->par->cor = 'b';
				y->cor = 'b';
				z->par->par->cor = 'r';
				if (z->par->par != NULL)
					z = z->par->par;
			}
			else {
				if ((z->par->esq != NULL) && (z->num == z->par->esq->num)) {
					z = z->par;
					dirRotate(z);
				}
				z->par->cor = 'b';
				z->par->par->cor = 'r';
				esqRotate(z->par->par);
			}
		}
	}
	root->cor = 'b';
}

void insert(int val) {
	Arvore *z = (Arvore*)malloc(sizeof(Arvore));
	z->num = val;
	z->esq = NULL;
	z->dir = NULL;
	z->cor = 'r';
	Arvore *x = root;
	Arvore *y = NULL;
	if (root == NULL) {
		root = z;
		root->cor = 'b';
		return;
	}
	while (x != NULL) {
		y = x;
		if (z->num < x->num) {
			x = x->esq;
		}
		else x = x->dir;
	}
	z->par = y;
	if (y == NULL) {
		root = z;
	}
	else if (z->num < y->num) {
		y->esq = z;
	}
	else y->dir = z;
	insereCor(z);

	return;
}
/*
void insert(int valor) {
	Arvore *z = (Arvore*)malloc(sizeof(Arvore));

	z->num = valor;
	z->esq = NULL;
	z->dir = NULL;
	z->cor = 'r';
	Arvore *x = root;
	Arvore *y = NULL;
	if (search(valor) == 1) {
		printf("Valor ja está na Arvore\n");
		return;
	}

	if (root == NULL) {
		root = z;
		root->cor = 'b';
		return;
	}
	while (x != NULL) {
		y = x;
		if (z->num < x->num)
			x = x->esq;
		else
			x = x->dir;
	}
	z->par = y;
	if (y == NULL)
		root = z;
	else if (z->num < y->num)
		y->esq = z;
	else
		y->dir = z;
	insereCor(z);

	return;
}

*/
void inorder(Arvore *root) {
	Arvore *temp = root;
	if (temp != NULL) {
		inorder(temp->esq);
		printf("valor [%d] cor [%c]\n", temp->num, temp->cor);
		inorder(temp->dir);
	}
	return;
}

void posoder(Arvore *root) {
	Arvore *temp = root;
	if (temp != NULL) {
		posoder(temp->esq);
		posoder(temp->dir);
		printf("valor [%d] cor [%c]\n", temp->num, temp->cor);
	}
	return;
}

void exibir(Arvore *root) {
	if (root != NULL) {
		printf("Em order \n");
		inorder(root);
		printf("Pos order \n");
		posoder(root);

	}
	return;
}

int search(int valor) {
	Arvore *temp = root;
	int dif;
	while (temp != NULL) {
		dif = valor - temp->num;
		if (dif > 0)
			temp = temp->dir;
		else if (dif < 0)
			temp = temp->esq;
		else {
			printf("Elemento achado\n");
			return 1;
		}
	}
	return 0;
}

Arvore *min(Arvore *x) {
	while (x->esq)
		x = x->esq;
	return x;
}

Arvore *sucessor(Arvore *x) {
	Arvore *y;

	if (x->dir)
		return min(x->dir);
	y = x->par;
	while (y && x == y->dir) {
		x = y;
		y = y->par;
	}
	return y;

}

void deletaCor(Arvore *x) {
	while (x != root && x->cor == 'b') {
		Arvore *w = NULL;

		if ((x->par->esq != NULL) && (x == x->par->esq)) {
			w = x->par->dir;
			if ((w != NULL) && (w->cor == 'r')) {
				w->cor = 'b';
				x->par->cor = 'r';
				esqRotate(x->par);
				w = x->par->dir;
			}
			if ((w != NULL) && (w->dir != NULL) && (w->esq != NULL) && (w->esq->cor == 'b') && (w->dir->cor == 'b')) {
				w->cor = 'r';
				x = x->par;
			}
			else if ((w != NULL) && (w->dir->cor == 'b')) {
				w->esq->cor = 'b';
				w->cor = 'r';
				dirRotate(w);
				w = x->par->dir;
			}
			if (w != NULL) {
				w->cor = x->par->cor;
				x->par->cor = 'b';
				w->dir->cor = 'b';
				esqRotate(x->par);
				x = root;
			}
		}
		else if (x->par != NULL) {
			w = x->par->esq;
			if ((w != NULL) && (w->cor == 'r')) {
				w->cor = 'b';
				x->par->cor = 'r';
				esqRotate(x->par);
				if (x->par != NULL)
					w = x->par->esq;
			}
			if ((w != NULL) && (w->dir != NULL) && (w->esq != NULL) && (w->dir->cor == 'b') && (w->esq->cor == 'b'))
				x = x->par;
			else if ((w != NULL) && (w->dir != NULL) && (w->esq != NULL) && (w->esq->cor == 'b')) {
				w->dir->cor = 'b';
				w->cor = 'r';
				dirRotate(w);
				w = x->par->esq;
			}
			if (x->par != NULL) {
				w->cor = x->par->cor;
				x->par->cor = 'b';
			}
			if (w->esq != NULL)
				w->esq->cor = 'b';
			if (x->par != NULL)
				esqRotate(x->par);

			x = root;
		}
	}
	x->cor = 'b';
}

Arvore *delete(int valor) {
	Arvore *x = NULL, *y = NULL, *z;
	z = root;

	if ((z->esq == NULL) && (z->dir == NULL) && (z->num == valor)) {
		root = NULL;
		printf("Arvore Rubro Negra está limpa \n");
		return;
	}
	while (z->num != valor  && z != NULL) {
		if (valor)
			z = z->esq;
		else
			z = z->dir;
		if (z == NULL)
			return;
	}
	if ((z->esq == NULL) || (z->dir == NULL))
		y = z;
	else
		y = sucessor(z);
	if (y->esq != NULL)
		x = y->esq;
	else {
		if (y->dir != NULL)
			x = y->dir;
	}
	if ((x != NULL) && (y->par != NULL))
		x->par = y->par;
	if ((y != NULL) && (x != NULL) && (y->par == NULL))
		root = x;
	else if (y == y->par->esq)
		y->par->esq = x;
	else
		y->par->dir = x;
	if (y != z)
		z->num = y->num;
	if ((y != NULL) && (x != NULL) && (y->cor == 'b'))
		deletaCor(x);


	return y;
}

int main() {
	int num, op;
	do{
		printf("1.Inserir \n2.Remover \n3.Buscar \n4.Exibir \n0.Sair\n");
	scanf("%d", &op);
	switch (op) {
	case 1:
		system("cls");
		printf("Entre com valor:\n>");
		scanf("%d", &num);
		insert(num);
		break;
	case 2:
		system("cls");
		printf("Entre com valor a ser removido\n>");
		scanf("%d", &num);
		delete(num);
		break;
	case 3:
		system("cls");
		printf("Entre com valor a ser buscado\n>");
		scanf("%d", &num);
		search(num);
		break;
	case 4:
		system("cls");
		printf("\n>");
		exibir(root);
		printf("\n");
		break;
	case 0:
		break;
	default:
		printf("Opção Invalida \n");
		break;
	}
	} while (op != 0);
}