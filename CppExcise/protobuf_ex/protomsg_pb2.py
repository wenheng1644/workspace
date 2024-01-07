# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: protomsg.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='protomsg.proto',
  package='persion',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=_b('\n\x0eprotomsg.proto\x12\x07persion\"1\n\x07Persion\x12\x0c\n\x04name\x18\x01 \x01(\t\x12\x0b\n\x03\x61ge\x18\x02 \x01(\x05\x12\x0b\n\x03sex\x18\x03 \x01(\x05\"E\n\x07\x43hatCmd\x12\x1b\n\x01p\x18\x01 \x01(\x0b\x32\x10.persion.Persion\x12\x0c\n\x04time\x18\x02 \x01(\x04\x12\x0f\n\x07\x63ontent\x18\x03 \x01(\t\"\x88\x01\n\x0bPersionList\x12,\n\x04list\x18\x01 \x03(\x0b\x32\x1e.persion.PersionList.ListEntry\x12\x0c\n\x04time\x18\x02 \x01(\x04\x1a=\n\tListEntry\x12\x0b\n\x03key\x18\x01 \x01(\x05\x12\x1f\n\x05value\x18\x02 \x01(\x0b\x32\x10.persion.Persion:\x02\x38\x01\x62\x06proto3')
)




_PERSION = _descriptor.Descriptor(
  name='Persion',
  full_name='persion.Persion',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='name', full_name='persion.Persion.name', index=0,
      number=1, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='age', full_name='persion.Persion.age', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='sex', full_name='persion.Persion.sex', index=2,
      number=3, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=27,
  serialized_end=76,
)


_CHATCMD = _descriptor.Descriptor(
  name='ChatCmd',
  full_name='persion.ChatCmd',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='p', full_name='persion.ChatCmd.p', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='time', full_name='persion.ChatCmd.time', index=1,
      number=2, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='content', full_name='persion.ChatCmd.content', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=78,
  serialized_end=147,
)


_PERSIONLIST_LISTENTRY = _descriptor.Descriptor(
  name='ListEntry',
  full_name='persion.PersionList.ListEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='persion.PersionList.ListEntry.key', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='persion.PersionList.ListEntry.value', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=_b('8\001'),
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=225,
  serialized_end=286,
)

_PERSIONLIST = _descriptor.Descriptor(
  name='PersionList',
  full_name='persion.PersionList',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='list', full_name='persion.PersionList.list', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='time', full_name='persion.PersionList.time', index=1,
      number=2, type=4, cpp_type=4, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[_PERSIONLIST_LISTENTRY, ],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=150,
  serialized_end=286,
)

_CHATCMD.fields_by_name['p'].message_type = _PERSION
_PERSIONLIST_LISTENTRY.fields_by_name['value'].message_type = _PERSION
_PERSIONLIST_LISTENTRY.containing_type = _PERSIONLIST
_PERSIONLIST.fields_by_name['list'].message_type = _PERSIONLIST_LISTENTRY
DESCRIPTOR.message_types_by_name['Persion'] = _PERSION
DESCRIPTOR.message_types_by_name['ChatCmd'] = _CHATCMD
DESCRIPTOR.message_types_by_name['PersionList'] = _PERSIONLIST
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Persion = _reflection.GeneratedProtocolMessageType('Persion', (_message.Message,), dict(
  DESCRIPTOR = _PERSION,
  __module__ = 'protomsg_pb2'
  # @@protoc_insertion_point(class_scope:persion.Persion)
  ))
_sym_db.RegisterMessage(Persion)

ChatCmd = _reflection.GeneratedProtocolMessageType('ChatCmd', (_message.Message,), dict(
  DESCRIPTOR = _CHATCMD,
  __module__ = 'protomsg_pb2'
  # @@protoc_insertion_point(class_scope:persion.ChatCmd)
  ))
_sym_db.RegisterMessage(ChatCmd)

PersionList = _reflection.GeneratedProtocolMessageType('PersionList', (_message.Message,), dict(

  ListEntry = _reflection.GeneratedProtocolMessageType('ListEntry', (_message.Message,), dict(
    DESCRIPTOR = _PERSIONLIST_LISTENTRY,
    __module__ = 'protomsg_pb2'
    # @@protoc_insertion_point(class_scope:persion.PersionList.ListEntry)
    ))
  ,
  DESCRIPTOR = _PERSIONLIST,
  __module__ = 'protomsg_pb2'
  # @@protoc_insertion_point(class_scope:persion.PersionList)
  ))
_sym_db.RegisterMessage(PersionList)
_sym_db.RegisterMessage(PersionList.ListEntry)


_PERSIONLIST_LISTENTRY._options = None
# @@protoc_insertion_point(module_scope)