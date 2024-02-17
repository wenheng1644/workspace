// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ConnectionCmd.proto

#include "ConnectionCmd.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace Connection {
PROTOBUF_CONSTEXPR ConnectionReqCmd::ConnectionReqCmd(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.m_account_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.m_passwd_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct ConnectionReqCmdDefaultTypeInternal {
  PROTOBUF_CONSTEXPR ConnectionReqCmdDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~ConnectionReqCmdDefaultTypeInternal() {}
  union {
    ConnectionReqCmd _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 ConnectionReqCmdDefaultTypeInternal _ConnectionReqCmd_default_instance_;
}  // namespace Connection
static ::_pb::Metadata file_level_metadata_ConnectionCmd_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_ConnectionCmd_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_ConnectionCmd_2eproto = nullptr;

const uint32_t TableStruct_ConnectionCmd_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Connection::ConnectionReqCmd, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Connection::ConnectionReqCmd, _impl_.m_account_),
  PROTOBUF_FIELD_OFFSET(::Connection::ConnectionReqCmd, _impl_.m_passwd_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Connection::ConnectionReqCmd)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Connection::_ConnectionReqCmd_default_instance_._instance,
};

const char descriptor_table_protodef_ConnectionCmd_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\023ConnectionCmd.proto\022\nConnection\"7\n\020Con"
  "nectionReqCmd\022\021\n\tm_account\030\001 \001(\t\022\020\n\010m_pa"
  "sswd\030\002 \001(\tb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_ConnectionCmd_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_ConnectionCmd_2eproto = {
    false, false, 98, descriptor_table_protodef_ConnectionCmd_2eproto,
    "ConnectionCmd.proto",
    &descriptor_table_ConnectionCmd_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_ConnectionCmd_2eproto::offsets,
    file_level_metadata_ConnectionCmd_2eproto, file_level_enum_descriptors_ConnectionCmd_2eproto,
    file_level_service_descriptors_ConnectionCmd_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_ConnectionCmd_2eproto_getter() {
  return &descriptor_table_ConnectionCmd_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_ConnectionCmd_2eproto(&descriptor_table_ConnectionCmd_2eproto);
namespace Connection {

// ===================================================================

class ConnectionReqCmd::_Internal {
 public:
};

ConnectionReqCmd::ConnectionReqCmd(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Connection.ConnectionReqCmd)
}
ConnectionReqCmd::ConnectionReqCmd(const ConnectionReqCmd& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  ConnectionReqCmd* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.m_account_){}
    , decltype(_impl_.m_passwd_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.m_account_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.m_account_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_m_account().empty()) {
    _this->_impl_.m_account_.Set(from._internal_m_account(), 
      _this->GetArenaForAllocation());
  }
  _impl_.m_passwd_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.m_passwd_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_m_passwd().empty()) {
    _this->_impl_.m_passwd_.Set(from._internal_m_passwd(), 
      _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:Connection.ConnectionReqCmd)
}

inline void ConnectionReqCmd::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.m_account_){}
    , decltype(_impl_.m_passwd_){}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.m_account_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.m_account_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.m_passwd_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.m_passwd_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

ConnectionReqCmd::~ConnectionReqCmd() {
  // @@protoc_insertion_point(destructor:Connection.ConnectionReqCmd)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void ConnectionReqCmd::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.m_account_.Destroy();
  _impl_.m_passwd_.Destroy();
}

void ConnectionReqCmd::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void ConnectionReqCmd::Clear() {
// @@protoc_insertion_point(message_clear_start:Connection.ConnectionReqCmd)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.m_account_.ClearToEmpty();
  _impl_.m_passwd_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ConnectionReqCmd::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string m_account = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_m_account();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Connection.ConnectionReqCmd.m_account"));
        } else
          goto handle_unusual;
        continue;
      // string m_passwd = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_m_passwd();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Connection.ConnectionReqCmd.m_passwd"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* ConnectionReqCmd::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Connection.ConnectionReqCmd)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string m_account = 1;
  if (!this->_internal_m_account().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_m_account().data(), static_cast<int>(this->_internal_m_account().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Connection.ConnectionReqCmd.m_account");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_m_account(), target);
  }

  // string m_passwd = 2;
  if (!this->_internal_m_passwd().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_m_passwd().data(), static_cast<int>(this->_internal_m_passwd().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Connection.ConnectionReqCmd.m_passwd");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_m_passwd(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Connection.ConnectionReqCmd)
  return target;
}

size_t ConnectionReqCmd::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Connection.ConnectionReqCmd)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string m_account = 1;
  if (!this->_internal_m_account().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_m_account());
  }

  // string m_passwd = 2;
  if (!this->_internal_m_passwd().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_m_passwd());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData ConnectionReqCmd::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    ConnectionReqCmd::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*ConnectionReqCmd::GetClassData() const { return &_class_data_; }


void ConnectionReqCmd::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<ConnectionReqCmd*>(&to_msg);
  auto& from = static_cast<const ConnectionReqCmd&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Connection.ConnectionReqCmd)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_m_account().empty()) {
    _this->_internal_set_m_account(from._internal_m_account());
  }
  if (!from._internal_m_passwd().empty()) {
    _this->_internal_set_m_passwd(from._internal_m_passwd());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void ConnectionReqCmd::CopyFrom(const ConnectionReqCmd& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Connection.ConnectionReqCmd)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ConnectionReqCmd::IsInitialized() const {
  return true;
}

void ConnectionReqCmd::InternalSwap(ConnectionReqCmd* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.m_account_, lhs_arena,
      &other->_impl_.m_account_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.m_passwd_, lhs_arena,
      &other->_impl_.m_passwd_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata ConnectionReqCmd::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_ConnectionCmd_2eproto_getter, &descriptor_table_ConnectionCmd_2eproto_once,
      file_level_metadata_ConnectionCmd_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Connection
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Connection::ConnectionReqCmd*
Arena::CreateMaybeMessage< ::Connection::ConnectionReqCmd >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Connection::ConnectionReqCmd >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
