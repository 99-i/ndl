from typing import List
import gdb

def print_root(val: gdb.Value):
    if(val['err'] == True):
        ret = ["Error: \"" + val['err_str'].string() + "\""]
    else:
        ret = ["Error: <none>"]
    ret.append("Filename: \"" + val['filename'].string() + "\"")
    return ret

def print_network(val: gdb.Value):
    ret = ["Name: \"" + val['network_name'].string() + "\""]
    return ret

def print_tensor(val: gdb.Value):
    size = val['dims']['dims_size']
    ret = ["Dimensions: [" + ", ".join([str(val['dims']['dims'][i]) for i in range(size)]) + "]"]
    ret.append("Name: " + str(val['name']))
    return ret


class NodePrinter:
    def __init__(self, val: gdb.Value):
        self.val = val

    def to_string(self, tab_level = 1):
        node_type = int(self.val['type'])
        tabs = "\t" * tab_level

        if node_type == 0:
            field = "root"
        elif node_type == 1:
            field = "network"
        elif node_type == 2:
            field = "statement"
        elif node_type == 3:
            field = "tensor"
        else:
            field = "<unknown>"

        result = [("\t" if tab_level == 1 else "") + "node (type = {})".format(self.val['type'])]

        union_val = self.val[field]
        if field == "root":
            result += map(lambda x: "\t" + x, print_root(union_val))
        elif field == "network":
            result += map(lambda x: "\t" + x, print_network(union_val))
        elif field == "tensor":
            result += map(lambda x: "\t" + x, print_tensor(union_val))


        children_size = int(self.val['children_size'])
        if children_size > 0:
            result.append("children ({}):".format(children_size))
            children = self.val['children']
            if children_size > 0:
                child_list: List[gdb.Value] = []
                for i in range(children_size):
                    child_list.append(children[i])
    
                child = list(map(lambda x: NodePrinter(x).to_string(tab_level + 1), child_list))
                child[0] = "\t" + child[0]
    
                result += child

        return ("\n" + tabs).join(result)

def node_lookup(val: gdb.Value):
    try:
        type_tag = val.type.strip_typedefs().tag
    except Exception:
        type_tag = None
    if type_tag == "node":
        return NodePrinter(val)
    return None

objfile = gdb.current_objfile()

if objfile:
    objfile.pretty_printers.append(node_lookup)
else:
    gdb.pretty_printers.append(node_lookup)
