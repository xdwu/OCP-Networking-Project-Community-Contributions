switch_inited=0

def switch_init(client):
    global switch_inited
    if switch_inited:
        return

    switch_attr_list = client.sai_thrift_get_switch_attribute()
    attr_list = switch_attr_list.attr_list
    for attribute in attr_list:
        if attribute.id == 0:
            print "max ports: " + attribute.value.u32
        elif attribute.id == 1:
            for x in attribute.value.objlist.object_id_list:
                port_list.append(x)
        else:
            print "unknown switch attribute"

    attr_value = sai_thrift_attribute_value_t(mac='00:77:66:55:44:33')
    attr = sai_thrift_attribute_t(id=22, value=attr_value)
    client.sai_thrift_set_switch_attribute(attr)
    switch_inited = 1

def sai_thrift_create_fdb(client, vlan_id, mac, port, mac_action):
    fdb_entry = sai_thrift_fdb_entry_t(mac_address=mac, vlan_id=vlan_id)
    #value 0 represents static entry, id=0, represents entry type
    fdb_attribute1_value = sai_thrift_attribute_value_t(u8=1)
    fdb_attribute1 = sai_thrift_attribute_t(id=0, value=fdb_attribute1_value)
    #value oid represents object id, id=1 represents port id
    fdb_attribute2_value = sai_thrift_attribute_value_t(oid=port)
    fdb_attribute2 = sai_thrift_attribute_t(id=1, value=fdb_attribute2_value)
    #value oid represents object id, id=1 represents port id
    fdb_attribute3_value = sai_thrift_attribute_value_t(u8=mac_action)
    fdb_attribute3 = sai_thrift_attribute_t(id=2, value=fdb_attribute3_value)
    fdb_attr_list = [fdb_attribute1, fdb_attribute2, fdb_attribute3]
    client.sai_thrift_create_fdb_entry(thrift_fdb_entry=fdb_entry, thrift_attr_list=fdb_attr_list)

def sai_thrift_delete_fdb(client, vlan_id, mac, port):
    fdb_entry = sai_thrift_fdb_entry_t(mac_address=mac, vlan_id=vlan_id)
    client.sai_thrift_delete_fdb_entry(thrift_fdb_entry=fdb_entry)

