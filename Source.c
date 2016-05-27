#include <stdio.h>
#pragma warning(disable : 4996)
typedef struct ArvoreRBN {
	int num;
	char color;
	struct ArvoreRBN *esq, *dir, *par;
}Arvore;
Arvore *root = NULL;

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

void insereCor(Arvore *z) {
	Arvore *y = NULL;

	while ((z->par != NULL) && (z->par->color == 'r')) {

		if ((z->par->par->esq != NULL) && (z->par->num == z->par->par->esq->num)) {

			if (z->par->par->dir != NULL)
				y = z->par->par->dir;
			if ((y != NULL) && (y->color == 'r')) {
				z->par->color = 'b';

				y->color = 'b';
				z->par->par->color = 'r';
				if (z->par->par != NULL)
					z = z->par->par;
			}
			else {
				if ((z->par->dir != NULL) && (z->num == z->par->dir->num)) {
					z = z->par;
					esqRotate(z);
				}
				z->par->color = 'b';
				z->par->par->color = 'r';
				dirRotate(z->par->par);

			}
		}
		else {

			if (z->par->par->esq != NULL)
				y = z->par->par->esq;

			if ((y != NULL) && (y->color == 'r')) {
				z->par->color = 'b';
				y->color = 'b';
				z->par->par->color = 'r';
				if (z->par->par != NULL)
					z = z->par->par;
			}
			else {

				if ((z->par->esq != NULL) && (z->num == z->par->esq->num)) {
					z = z->par;
					dirRotate(z);
				}

				z->par->color = 'b';
				z->par->par->color = 'r';
				esqRotate(z->par->par);

			}
		}
	}
	root->color = 'b';
}

void insert(int val) {
	Arvore *x, *y = NULL;
	Arvore *z = (Arvore*)malloc(sizeof(Arvore));
	z->num = val;
	z->esq = NULL;
	z->dir = NULL;
	z->color = 'r';
	x = root;


	if (search(val) == 1) {
		printf("Elemento ja existe \n");
		return;
	}

	if (root == NULL) {
		root = z;
		root->color = 'b';
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

void inorder(Arvore* root) {

	Arvore* temp = root;

	if (temp != NULL) {
		inorder(temp->esq);
		printf("valor [%d] cor [%c]\n", temp->num, temp->cor);
		inorder(temp->dir);
	}
	return;
}

void posorder(Arvore* root) {
	Arvore* temp = root;

	if (temp != NULL) {
		posorder(temp->esq);
		posorder(temp->dir);
		printf("valor [%d] cor [%c]\n", temp->num, temp->cor);
	}
	return;

}

void exibir(Arvore* root) {
	if (root != NULL) {
		printf("valor [%d] cor [%c]\n", temp->num, temp->cor);
		printf("Em order \n");
		inorder(root);
		printf("Pos order \n");
		posorder(root);
	}
	return;

}

int search(int val) {
	Arvore* temp = root;
	int diff;
	while (temp != NULL) {
		diff = val - temp->num;
		if (diff > 0)
			temp = temp->dir;
		else if (diff < 0)
			temp = temp->esq;
		else {
			printf("Elemento Encontrado \n");
			return 1;
		}

	}
	return 0;
}

Arvore* min(Arvore *x) {

	while (x->esq)
		x = x->esq;

	return x;
}
Arvore* sucessor(Arvore *x) {
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
	while (x != root && x->color == 'b') {
		Arvore *w = NULL;

		if ((x->par->esq != NULL) && (x == x->par->esq)) {
			w = x->par->dir;

			if ((w != NULL) && (w->color == 'r')) {
				w->color = 'b';

				x->par->color = 'r';
				esqRotate(x->par);
				w = x->par->dir;
			}

			if ((w != NULL) && (w->dir != NULL) && (w->esq != NULL) && (w->esq->color == 'b') && (w->dir->color == 'b')) {
				w->color = 'r';
				x = x->par;
			}

			else if ((w != NULL) && (w->dir->color == 'b')) {
				w->esq->color = 'b';

				w->color = 'r';
				dirRotate(w);
				w = x->par->dir;

			}

			if (w != NULL)

			{
				w->color = x->par->color;

				x->par->color = 'b';
				w->dir->color = 'b';
				esqRotate(x->par);
				x = root;
			}

		}
		else if (x->par != NULL) {
			w = x->par->esq;

			if ((w != NULL) && (w->color == 'r')) {
				w->color = 'b';
				x->par->color = 'r';
				esqRotate(x->par);
				if (x->par != NULL)
					w = x->par->esq;

			}

			if ((w != NULL) && (w->dir != NULL) && (w->esq != NULL) && (w->dir->color == 'b') && (w->esq->color == 'b'))
				x = x->par;

			else if ((w != NULL) && (w->dir != NULL) && (w->esq != NULL) && (w->esq->color == 'b')) {
				w->dir->color = 'b';
				w->color = 'r';
				dirRotate(w);
				w = x->par->esq;

			}

			if (x->par != NULL) {
				w->color = x->par->color;
				x->par->color = 'b';

			}

			if (w->esq != NULL)
				w->esq->color = 'b';

			if (x->par != NULL)
				esqRotate(x->par);
			x = root;

		}

	}
	x->color = 'b';

}

Arvore* delete(int var) {
	Arvore *x = NULL, *y = NULL, *z;
	z = root;

	if ((z->esq == NULL) && (z->dir == NULL) && (z->num == var)) {
		root = NULL;
		printf("Arvore Rubro Negra está limpa \n");
		return;
	}

	while (z->num != var && z != NULL) {
		if (var)
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
	if ((y != NULL) && (x != NULL) && (y->color == 'b'))
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
