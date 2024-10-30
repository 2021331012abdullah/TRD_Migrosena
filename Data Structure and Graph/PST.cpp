int root[N];
int st[60*N];
int lc[60*N];
int rc[60*N];
int ct;

int build(int ss,int se)
{
    int node = ++ct;
   
    if(ss == se) return node;
    
    int mid = (ss+se)/2;
    
    lc[node] = build(ss,mid);
    rc[node] = build(mid+1,se);
    
    return node;
}

int upd(int old,int ss,int se,int id,int val)
{ 
    int node = ++ct;
    
    if(ss == se)
    {
        st[node] = st[old] + val;
        return node;
    }
    
    int mid = (ss + se)/2;
    
    if(id <= mid)
        lc[node] = upd(lc[old],ss,mid,id,val),rc[node] = rc[old];
    else
        rc[node] = upd(rc[old],mid+1,se,id,val),lc[node] = lc[old];
    
    st[node] = st[lc[node]] + st[rc[node]];
    
    return node;
}

int query(int node,int ss,int se,int l,int r)
{
    if(ss > r || se < l) return 0;
    
    if(l <= ss && se <= r) return st[node];
    
    int mid = (ss + se)/2;
    
    return query(lc[node],ss,mid,l,r) + query(rc[node],mid+1,se,l,r);
}