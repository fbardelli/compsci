

struct AvlNode {
   int data;
   AvlNode  *left;
   AvlNode  *right;
   int     height;
   AvlNode( int d, AvlNode *lt, AvlNode *rt, int h = 0 ) : data( theElement ), left( lt ), right( rt ), height( h );
};

/*
 *    Rotate Binary tree node with left child.
 *       Update heights, then set new root.
 *       */
void rotateWithLeftChild( AvlNode * & k2 )
{
   AvlNode *k1 = k2->left;
   k2->left = k1->right;
   k1->right = k2;
   k2->height = max( height( k2->left ), height( k2->right ) ) +1;
   k1->height = max( height( k1->left ), k2->height ) +1;
   k2 = k1;
}

/*
 *    Return the height of node t or -1 if NULL.
 *    */
int height( AvlNode *t ) const
{
   return t == NULL ? -1 : t->height;
}


/*
 *    Rotate Binary tree node with right child.
 *       Update heights, then set new root.
 *       */
void rotateWithRightChild( AvlNode * & k2 )
{
   AvlNode *k1 = k2->right;
   k2->right = k1->left;
   k1->left = k2;
   k2->height = max( height( k2->right ), height( k2->left ) ) +1;
   k1->height = max( height( k1->right ), k2->height ) +1;
   k2 = k1;
}

/*
 *    Double rotate binary tree: first left child
 *       with its right child; then node k3 with new left child.
 *          Update heights, then set new root.
 *          */
void doubleWithLeftChild( AvlNode * & k3 )
{
   rotateWithRightChild( k3->left );
   rotateWithLeftChild( k3 );
}

/*
 *    Internal method to insert into a subtree
 *       x is the item to insert
 *          t is the node that roots the subtree
 *             Set the new root of the subtree
 *             */
void insert( int x, AvlNode * & t )
{
        if( t == NULL )
                t = new AvlNode( x, NULL, NULL );
        else if( x < t->data )
        {
                insert( x, t->left );
                if( height( t->left ) - height( t->right ) == 2 )
                        if( x < t->left->data )
                                rotateWithRightChild( t );
                        else
                                doubleWithLeftChild( t );
        }
        else if( t->data < x )
        {
                insert( x, t->right );
                if( height( t->right ) - height( t->left ) == 2 )
                        if( x < t->left->data )
                                rotateWithRightChild( t );
                        else
                                doubleWithLeftChild( t );
        }
        else
                ; // Duplicate; do nothing
        t->height = max( height( t->left ), height( t->right ) ) + 1;
        
}

