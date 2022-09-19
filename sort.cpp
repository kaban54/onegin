#include "onegin.h"


void Quicksort (void *data, size_t len, size_t size, int (*comp)(const void*, const void*))
{
    if (len <= 2)
    {
        if (len == 2) SortTwo (data, size, comp);
        return;
    }

    void *central = partition (data, len, size, comp);
    size_t len1 = ((size_t) central - (size_t) data) / size;

    Quicksort (data   , len1      , size, comp);
    Quicksort (central, len - len1, size, comp);
}

void *partition (void *data, size_t len, size_t size, int (*comp)(const void*, const void*))
{
    char *il = (char *) data;
    char *ir = (char *) data +  (len - 1)      * size;
    char *c  = (char *) data + ((len - 1) / 2) * size;

    if (comp (il, c) > 0) swap (il, c, size);
    if (comp (c, ir) > 0) swap (c, ir, size);
    if (comp (il, c) > 0) swap (il, c, size);

    if (len == 3) return (void *) c;

    while (il < ir)
    {
        while (il < ir && comp(il, c) <= 0) il += size;

        while (il < ir && comp(ir, c) >= 0) ir -= size;

        if (il >= ir) break;

        swap (il, ir, size);
    }

    return il;
}

void SortTwo (void *data, size_t size, int (*comp)(const void*, const void*))
{
    void *p1 = data;
    void *p2 = (void *) ((char *) p1 + size);

    if (comp (p1, p2) > 0) swap (p1, p2, size); 
}

void swap (void *pointer1, void *pointer2, size_t size)
{
    if (pointer1 == pointer2 || pointer1 == NULL || pointer2 == NULL) return;

    char *p1 = (char *)pointer1;
    char *p2 = (char *)pointer2;

    long long buf64 = 0;
    int       buf32 = 0;
    short     buf16 = 0;
    char      buf8  = 0;

    while (size >= sizeof (buf64))
    {
        buf64 = *(long long *)(p1);
        *(long long *)(p1) = *(long long *)(p2);
        *(long long *)(p2) = buf64;

        p1 += sizeof (buf64);
        p2 += sizeof (buf64);
        size -= sizeof (buf64);
    }

    if (size >= sizeof (buf32))
    {
        
        buf32 = *(int *)(p1);
        *(int *)(p1) = *(int *)(p2);
        *(int *)(p2) = buf32;

        p1 += sizeof (buf32);
        p2 += sizeof (buf32);
        size -= sizeof (buf32);
    }
 
    if (size >= sizeof (buf16))
    {
        
        buf16 = *(short *)(p1);
        *(short *)(p1) = *(short *)(p2);
        *(short *)(p2) = buf16;

        p1 += sizeof (buf16);
        p2 += sizeof (buf16);
        size -= sizeof (buf16);
    }
 
    if (size >= sizeof (buf8))
    {
        
        buf8 = *(char *)(p1);
        *(char *)(p1) = *(char *)(p2);
        *(char *)(p2) = buf8;

        p1 += sizeof (buf8);
        p2 += sizeof (buf8);
        size -= sizeof (buf8);
    }

}


int CompFwd (const void *p1, const void *p2)
{
    if (p1 == NULL || p2 == NULL) return 0;
    if (p1 == p2) return 0;

    char *s1 = ((struct Line*) p1) -> str;
    char *s2 = ((struct Line*) p2) -> str;

    int comp = 1;

    while (1)
    {
        if (*s1 == '\0') return (*s2 == '\0' ? 0 : -1);
        if (*s2 == '\0') return 1;

        if (!isalpha(*s1))
        {
            s1++;
            continue;
        }

        if (!isalpha(*s2))
        {
            s2++;
            continue;
        }

        comp = tolower (*s1) - tolower (*s2);

        if (comp != 0) return comp;

        s1++;
        s2++;
    }
}


int CompBwd (const void *p1, const void *p2)
{
    if (p1 == NULL || p2 == NULL) return 0;

    size_t len1 = ((struct Line*) p1) -> len;
    size_t len2 = ((struct Line*) p2) -> len;

    char *s1_beg = ((struct Line*) p1) -> str;
    char *s2_beg = ((struct Line*) p2) -> str;
    char *s1     = s1_beg + len1;
    char *s2     = s2_beg + len2;

    int comp = 1;
    
    while (1)
    {
        if (s1 < s1_beg) return (s2 < s2_beg ? 0 : -1);
        if (s2 < s2_beg) return 1;

        if (!isalpha(*s1))
        {
            s1--;
            continue;
        }

        if (!isalpha(*s2))
        {
            s2--;
            continue;
        }

        comp = tolower (*s1) - tolower (*s2);

        if (comp != 0) return comp;

        s1--;
        s2--;
    }
}
