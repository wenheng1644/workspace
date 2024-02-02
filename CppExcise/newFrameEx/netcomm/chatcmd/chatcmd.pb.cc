// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: chatcmd.proto

#include "chatcmd.pb.h"

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

namespace cmd {
PROTOBUF_CONSTEXPR chatMessageCmd::chatMessageCmd(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.content_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.status_)*/0u
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct chatMessageCmdDefaultTypeInternal {
  PROTOBUF_CONSTEXPR chatMessageCmdDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~chatMessageCmdDefaultTypeInternal() {}
  union {
    chatMessageCmd _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 chatMessageCmdDefaultTypeInternal _chatMessageCmd_default_instance_;
}  // namespace cmd
static ::_pb::Metadata file_level_metadata_chatcmd_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_chatcmd_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_chatcmd_2eproto = nullptr;

const uint32_t TableStruct_chatcmd_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::cmd::chatMessageCmd, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::cmd::chatMessageCmd, _impl_.content_),
  PROTOBUF_FIELD_OFFSET(::cmd::chatMessageCmd, _impl_.status_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::cmd::chatMessageCmd)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::cmd::_chatMessageCmd_default_instance_._instance,
};

const char descriptor_table_protodef_chatcmd_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\rchatcmd.proto\022\003cmd\"1\n\016chatMessageCmd\022\017"
  "\n\007content\030\001 \001(\t\022\016\n\006status\030\002 \001(\rb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_chatcmd_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_chatcmd_2eproto = {
    false, false, 79, descriptor_table_protodef_chatcmd_2eproto,
    "chatcmd.proto",
    &descriptor_table_chatcmd_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_chatcmd_2eproto::offsets,
    file_level_metadata_chatcmd_2eproto, file_level_enum_descriptors_chatcmd_2eproto,
    file_level_service_descriptors_chatcmd_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_chatcmd_2eproto_getter() {
  return &descriptor_table_chatcmd_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_chatcmd_2eproto(&descriptor_table_chatcmd_2eproto);
namespace cmd {

// ===================================================================

class chatMessageCmd::_Internal {
 public:
};

chatMessageCmd::chatMessageCmd(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:cmd.chatMessageCmd)
}
chatMessageCmd::chatMessageCmd(const chatMessageCmd& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  chatMessageCmd* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.content_){}
    , decltype(_impl_.status_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.content_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.content_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_content().empty()) {
    _this->_impl_.content_.Set(from._internal_content(), 
      _this->GetArenaForAllocation());
  }
  _this->_impl_.status_ = from._impl_.status_;
  // @@protoc_insertion_point(copy_constructor:cmd.chatMessageCmd)
}

inline void chatMessageCmd::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.content_){}
    , decltype(_impl_.status_){0u}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.content_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.content_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

chatMessageCmd::~chatMessageCmd() {
  // @@protoc_insertion_point(destructor:cmd.chatMessageCmd)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void chatMessageCmd::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.content_.Destroy();
}

void chatMessageCmd::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void chatMessageCmd::Clear() {
// @@protoc_insertion_point(message_clear_start:cmd.chatMessageCmd)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.content_.ClearToEmpty();
  _impl_.status_ = 0u;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* chatMessageCmd::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string content = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_content();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "cmd.chatMessageCmd.content"));
        } else
          goto handle_unusual;
        continue;
      // uint32 status = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.status_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
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

uint8_t* chatMessageCmd::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:cmd.chatMessageCmd)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string content = 1;
  if (!this->_internal_content().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_content().data(), static_cast<int>(this->_internal_content().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "cmd.chatMessageCmd.content");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_content(), target);
  }

  // uint32 status = 2;
  if (this->_internal_status() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(2, this->_internal_status(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:cmd.chatMessageCmd)
  return target;
}

size_t chatMessageCmd::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:cmd.chatMessageCmd)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string content = 1;
  if (!this->_internal_content().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_content());
  }

  // uint32 status = 2;
  if (this->_internal_status() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(this->_internal_status());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData chatMessageCmd::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    chatMessageCmd::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*chatMessageCmd::GetClassData() const { return &_class_data_; }


void chatMessageCmd::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<chatMessageCmd*>(&to_msg);
  auto& from = static_cast<const chatMessageCmd&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:cmd.chatMessageCmd)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_content().empty()) {
    _this->_internal_set_content(from._internal_content());
  }
  if (from._internal_status() != 0) {
    _this->_internal_set_status(from._internal_status());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void chatMessageCmd::CopyFrom(const chatMessageCmd& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:cmd.chatMessageCmd)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool chatMessageCmd::IsInitialized() const {
  return true;
}

void chatMessageCmd::InternalSwap(chatMessageCmd* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.content_, lhs_arena,
      &other->_impl_.content_, rhs_arena
  );
  swap(_impl_.status_, other->_impl_.status_);
}

::PROTOBUF_NAMESPACE_ID::Metadata chatMessageCmd::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_chatcmd_2eproto_getter, &descriptor_table_chatcmd_2eproto_once,
      file_level_metadata_chatcmd_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace cmd
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::cmd::chatMessageCmd*
Arena::CreateMaybeMessage< ::cmd::chatMessageCmd >(Arena* arena) {
  return Arena::CreateMessageInternal< ::cmd::chatMessageCmd >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>