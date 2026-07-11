#include "rive/artboard.hpp"
#include "rive/animation/state_machine_input_instance.hpp"
#include "rive/animation/state_machine_instance.hpp"
#include "rive/file.hpp"
#include "rive/layout.hpp"
#include "rive/math/aabb.hpp"
#include "rive/math/mat2d.hpp"
#include "rive/refcnt.hpp"
#include "rive/renderer.hpp"
#include "rive/renderer/metal/render_context_metal_impl.h"
#include "rive/renderer/render_context.hpp"
#include "rive/renderer/rive_renderer.hpp"

#import <Metal/Metal.h>

#include <memory>

namespace
{
struct MetalContext
{
    std::unique_ptr<rive::gpu::RenderContext> renderContext;
    std::unique_ptr<rive::RiveRenderer> renderer;
};
} // namespace

extern "C"
{
    using namespace rive;
    using namespace rive::gpu;

    MetalContext* rive_rs_metal_context_new(void* mtl_device)
    {
        auto render_context = RenderContextMetalImpl::MakeContext(
            (__bridge id<MTLDevice>)mtl_device);
        if (!render_context)
        {
            return nullptr;
        }

        auto* context = new MetalContext;
        context->renderer =
            std::make_unique<RiveRenderer>(render_context.get());
        context->renderContext = std::move(render_context);

        return context;
    }

    void rive_rs_metal_context_release(MetalContext* context)
    {
        delete context;
    }

    RenderTargetMetal* rive_rs_metal_render_target_new(MetalContext* context,
                                                       uint32_t pixel_format,
                                                       uint32_t width,
                                                       uint32_t height)
    {
        auto* impl = context->renderContext
                         ->static_impl_cast<RenderContextMetalImpl>();

        return impl->makeRenderTarget(
                       static_cast<MTLPixelFormat>(pixel_format),
                       width,
                       height)
            .release();
    }

    void rive_rs_metal_render_target_release(RenderTargetMetal* render_target)
    {
        safe_unref(render_target);
    }

    void rive_rs_metal_render_target_set_texture(
        RenderTargetMetal* render_target, void* mtl_texture)
    {
        render_target->setTargetTexture((__bridge id<MTLTexture>)mtl_texture);
    }

    const File* rive_rs_metal_file_new(MetalContext* context,
                                       const uint8_t* data,
                                       size_t len,
                                       ImportResult* result)
    {
        auto file =
            File::import({data, len}, context->renderContext.get(), result);

        return file.release();
    }

    void rive_rs_metal_file_release(const File* file)
    {
        std::unique_ptr<File> val(std::move(const_cast<File*>(file)));
    }

    size_t rive_rs_metal_file_artboard_count(const File* file)
    {
        return file->artboardCount();
    }

    void rive_rs_metal_instantiate_artboard(
        const File* file,
        const size_t* index,
        ArtboardInstance** artboard_instance)
    {
        if (index)
        {
            if (*index < file->artboardCount())
            {
                *artboard_instance = file->artboardAt(*index).release();
            }
        }
        else
        {
            auto ptr = file->artboardDefault();
            if (ptr)
            {
                *artboard_instance = ptr.release();
            }
        }

        if (*artboard_instance)
        {
            (*artboard_instance)->advance(0.0f);
        }
    }

    void rive_rs_metal_instantiate_artboard_by_name(
        const File* file,
        const char* data,
        size_t len,
        ArtboardInstance** artboard_instance)
    {
        *artboard_instance = file->artboardNamed({data, len}).release();

        if (*artboard_instance)
        {
            (*artboard_instance)->advance(0.0f);
        }
    }

    void rive_rs_metal_artboard_release(
        const ArtboardInstance* artboard_instance)
    {
        std::unique_ptr<ArtboardInstance> val(
            std::move(const_cast<ArtboardInstance*>(artboard_instance)));
    }

    float rive_rs_metal_artboard_width(
        const ArtboardInstance* artboard_instance)
    {
        return artboard_instance->bounds().width();
    }

    float rive_rs_metal_artboard_height(
        const ArtboardInstance* artboard_instance)
    {
        return artboard_instance->bounds().height();
    }

    void rive_rs_metal_instantiate_state_machine(
        ArtboardInstance* artboard_instance,
        const size_t* index,
        StateMachineInstance** state_machine)
    {
        if (index)
        {
            if (*index < (size_t)artboard_instance->stateMachineCount())
            {
                *state_machine =
                    artboard_instance->stateMachineAt(*index).release();
            }
        }
        else
        {
            auto ptr = artboard_instance->defaultStateMachine();
            if (ptr)
            {
                *state_machine = ptr.release();
            }
            else if (artboard_instance->stateMachineCount())
            {
                *state_machine =
                    artboard_instance->stateMachineAt(0).release();
            }
        }
    }

    void rive_rs_metal_instantiate_state_machine_by_name(
        ArtboardInstance* artboard_instance,
        const char* data,
        size_t len,
        StateMachineInstance** state_machine)
    {
        *state_machine =
            artboard_instance->stateMachineNamed({data, len}).release();
    }

    void rive_rs_metal_state_machine_release(
        const StateMachineInstance* state_machine)
    {
        std::unique_ptr<StateMachineInstance> val(
            std::move(const_cast<StateMachineInstance*>(state_machine)));
    }

    bool rive_rs_metal_state_machine_advance_and_apply(
        StateMachineInstance* state_machine, float elapsed)
    {
        return state_machine->advanceAndApply(elapsed);
    }

    void rive_rs_metal_state_machine_pointer_down(
        StateMachineInstance* state_machine, float x, float y)
    {
        state_machine->pointerDown({x, y});
    }

    void rive_rs_metal_state_machine_pointer_move(
        StateMachineInstance* state_machine, float x, float y)
    {
        state_machine->pointerMove({x, y});
    }

    void rive_rs_metal_state_machine_pointer_up(
        StateMachineInstance* state_machine, float x, float y)
    {
        state_machine->pointerUp({x, y});
    }

    SMIBool* rive_rs_metal_state_machine_get_bool(
        const StateMachineInstance* state_machine,
        const char* name,
        size_t len)
    {
        return state_machine->getBool({name, len});
    }

    SMINumber* rive_rs_metal_state_machine_get_number(
        const StateMachineInstance* state_machine,
        const char* name,
        size_t len)
    {
        return state_machine->getNumber({name, len});
    }

    SMITrigger* rive_rs_metal_state_machine_get_trigger(
        const StateMachineInstance* state_machine,
        const char* name,
        size_t len)
    {
        return state_machine->getTrigger({name, len});
    }

    bool rive_rs_metal_bool_get(const SMIBool* smi_bool)
    {
        return smi_bool->value();
    }

    void rive_rs_metal_bool_set(SMIBool* smi_bool, bool value)
    {
        smi_bool->value(value);
    }

    float rive_rs_metal_number_get(const SMINumber* smi_number)
    {
        return smi_number->value();
    }

    void rive_rs_metal_number_set(SMINumber* smi_number, float value)
    {
        smi_number->value(value);
    }

    void rive_rs_metal_trigger_fire(SMITrigger* smi_trigger)
    {
        smi_trigger->fire();
    }

    void rive_rs_metal_begin_frame(MetalContext* context,
                                   uint32_t width,
                                   uint32_t height,
                                   LoadAction load_action,
                                   uint32_t clear_color)
    {
        RenderContext::FrameDescriptor frame_descriptor;
        frame_descriptor.renderTargetWidth = width;
        frame_descriptor.renderTargetHeight = height;
        frame_descriptor.loadAction = load_action;
        frame_descriptor.clearColor = clear_color;
        context->renderContext->beginFrame(frame_descriptor);
    }

    void rive_rs_metal_draw_artboard(MetalContext* context,
                                     ArtboardInstance* artboard_instance,
                                     Fit fit,
                                     float alignment_x,
                                     float alignment_y,
                                     float scale_factor)
    {
        const auto& frame_descriptor =
            context->renderContext->frameDescriptor();
        AABB frame_bounds(
            0.0f,
            0.0f,
            static_cast<float>(frame_descriptor.renderTargetWidth),
            static_cast<float>(frame_descriptor.renderTargetHeight));

        context->renderer->save();
        context->renderer->align(fit,
                                 Alignment(alignment_x, alignment_y),
                                 frame_bounds,
                                 artboard_instance->bounds(),
                                 scale_factor);
        artboard_instance->draw(context->renderer.get());
        context->renderer->restore();
    }

    void rive_rs_metal_draw_artboard_with_transform(
        MetalContext* context,
        ArtboardInstance* artboard_instance,
        const float* transform)
    {
        context->renderer->save();
        context->renderer->transform(Mat2D(transform[0],
                                           transform[1],
                                           transform[2],
                                           transform[3],
                                           transform[4],
                                           transform[5]));
        artboard_instance->draw(context->renderer.get());
        context->renderer->restore();
    }

    void rive_rs_metal_flush(MetalContext* context,
                             RenderTargetMetal* render_target,
                             void* mtl_command_buffer)
    {
        RenderContext::FlushResources flush_resources;
        flush_resources.renderTarget = render_target;
        flush_resources.externalCommandBuffer = mtl_command_buffer;
        context->renderContext->flush(flush_resources);
    }

    void* rive_rs_metal_test_default_device(void)
    {
        return (__bridge_retained void*)MTLCreateSystemDefaultDevice();
    }

    void* rive_rs_metal_test_command_queue_new(void* mtl_device)
    {
        id<MTLDevice> device = (__bridge id<MTLDevice>)mtl_device;

        return (__bridge_retained void*)[device newCommandQueue];
    }

    void* rive_rs_metal_test_command_buffer_new(void* mtl_command_queue)
    {
        id<MTLCommandQueue> queue =
            (__bridge id<MTLCommandQueue>)mtl_command_queue;

        return (__bridge_retained void*)[queue commandBuffer];
    }

    void rive_rs_metal_test_command_buffer_commit_and_wait(
        void* mtl_command_buffer)
    {
        id<MTLCommandBuffer> command_buffer =
            (__bridge id<MTLCommandBuffer>)mtl_command_buffer;
        [command_buffer commit];
        [command_buffer waitUntilCompleted];
    }

    void* rive_rs_metal_test_texture_new(void* mtl_device,
                                         uint32_t pixel_format,
                                         uint32_t width,
                                         uint32_t height)
    {
        id<MTLDevice> device = (__bridge id<MTLDevice>)mtl_device;
        MTLTextureDescriptor* descriptor = [MTLTextureDescriptor
            texture2DDescriptorWithPixelFormat:static_cast<MTLPixelFormat>(
                                                   pixel_format)
                                         width:width
                                        height:height
                                     mipmapped:NO];
        descriptor.usage = MTLTextureUsageRenderTarget |
                           MTLTextureUsageShaderRead |
                           MTLTextureUsageShaderWrite;
        descriptor.storageMode = MTLStorageModeShared;

        return (__bridge_retained void*)[device
            newTextureWithDescriptor:descriptor];
    }

    void rive_rs_metal_test_texture_read(void* mtl_texture,
                                         uint8_t* out,
                                         uint32_t width,
                                         uint32_t height)
    {
        id<MTLTexture> texture = (__bridge id<MTLTexture>)mtl_texture;
        [texture getBytes:out
              bytesPerRow:width * 4
               fromRegion:MTLRegionMake2D(0, 0, width, height)
              mipmapLevel:0];
    }

    void rive_rs_metal_test_object_release(void* object)
    {
        if (object)
        {
            id val = (__bridge_transfer id)object;
            val = nil;
        }
    }
}
