#pragma once

#include "RenderStreamLink.h"
#include <initializer_list>
#include <vector>

class UWorld;
class AActor;

// Select a scene within the project, provide and apply parameters.
class RenderStreamSceneSelector
{
public:
    virtual ~RenderStreamSceneSelector();
    void LoadSchemas(const UWorld& world);
    virtual void ApplyScene(const UWorld& world, uint32_t sceneId) = 0;

protected:
    const RenderStreamLink::Schema& Schema() const;

    virtual bool OnLoadedSchema(const UWorld& World, const RenderStreamLink::Schema& Schema) = 0;
    bool ValidateParameters(const RenderStreamLink::RemoteParameters& sceneParameters, std::initializer_list<const AActor*> Actors) const;
    void ApplyParameters(uint32_t sceneId, std::initializer_list<AActor*> Actors) const;

private:
    size_t ValidateParameters(const AActor* Root, RenderStreamLink::RemoteParameter* const parameters, size_t numParameters) const;
    void ApplyParameters(AActor* Root, uint64_t specHash, const RenderStreamLink::RemoteParameter** ppParams, const float** ppFloatValues, const RenderStreamLink::ImageFrameData** ppImageValues) const;

    std::vector<uint8_t> m_schemaMem;
    RenderStreamLink::ScopedSchema m_defaultSchema;
};
