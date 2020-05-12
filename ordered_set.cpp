#include <ext/pb_ds/assoc_container.hpp> // Общий файл.
#include <ext/pb_ds/tree_policy.hpp> // Содержит класс tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<
        int,
        null_type,
        less<>,
        rb_tree_tag,
        tree_order_statistics_node_update>
        ordered_set;
