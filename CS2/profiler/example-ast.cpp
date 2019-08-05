/////////////////////////////////////////////////////////////////////////////
//KSU
//Spring 2019
//Example of source code and srcML
//Source code

int search(int tbl[], int n, int key) {
    int result = -1;
    for (int i = 0; i < n; ++i) {
        if (key == tbl[i]) {
            result = i;
        }
    }
    return result;
}

/////////////////////////////////////////////////////////////////////////////
//srcML version of source code
//Indented to show tree structure

<function>
    <type><name>int</name></type>
    <name>search</name>
    <parameter_list>(
        <param><decl><type><name>int</name></type> <name><name>tbl</name><index>[]</index></name></decl></param>,
        <param><decl><type><name>int</name></type> <name>n</name></decl></param>,
        <param><decl><type><name>int</name></type> <name>key</name></decl></param>
        )</parameter_list>
    <block>{
        <decl_stmt><decl><type><name>int</name></type> <name>result</name> =<init> <expr>-1</expr></init></decl>;</decl_stmt>
        <for>for (<init><decl><type><name>int</name></type> <name>i</name> =<init> <expr>0</expr></init></decl>;
                  </init> <condition><expr><name>i</name> &lt;
                  <name>n</name></expr>;</condition> <incr><expr>++<name>i</name></expr></incr>)
                  <block>{
                      <if>if <condition>(<expr><name>key</name> == <name><name>tbl</name><index>[<expr><name>i</name></expr>]</index></name></expr>)</condition><then>
                          <block>{
                              <expr_stmt><expr><name>result</name> = <name>i</name></expr>;</expr_stmt>
                          }</block></then></if>
        }</block></for>
        <return>return <expr><name>result</name></expr>;</return>
    }</block>
</function>
