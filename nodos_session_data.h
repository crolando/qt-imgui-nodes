#ifndef NODOS_SESSION_DATA_H
#define NODOS_SESSION_DATA_H
#include <nodos.h>
#include <node.h>
#include <node_utils.h>

struct nodos_session_data {
    std::vector<Node>    s_Nodes;   // The index is NOT the ID!
    std::map<std::string, nodos::NodeDescription> NodeRegistry;
    void RegisterNewNode(nodos::NodeDescription NewDescription) {
        NodeRegistry[NewDescription.Type] = NewDescription;
    }

    // Used in Deserialization (loading material from a save file) routines.
    // Very similar to NewRegistryNode but with different ID
    void RestoreRegistryNode(const std::string& NodeName,const std::string* Properties, int id)
    {
        // Standard node spawner behavior, only we construct the objects
        // using the registry data.
        // NodeRegistry is a map, so we need the value.
        nodos::NodeDescription Desc = NodeRegistry[NodeName];

        // Create node object and pass the type name.
        s_Nodes.emplace_back(id, Desc.Type.c_str());
        // Because we didn't call GetNextID, we must manually put the ID counter where it
        // would be, had we done so.
        SetNextId(id + 1);

        // Handle creating the pins
        for(nodos::PinDescription p : Desc.Inputs)
            s_Nodes.back().Inputs.emplace_back(GetNextId(), p.Label.c_str(), PinType::Flow);
        for(nodos::PinDescription p : Desc.Outputs)
            s_Nodes.back().Outputs.emplace_back(GetNextId(), p.Label.c_str(), PinType::Flow);

        // Handle properties
            s_Nodes.back().Properties.deseralize(*Properties);


        // Standard scrubber from examples.
        BuildNode(&s_Nodes.back());
    }

    Node* NewRegistryNode(const std::string& NodeName)
    {

        // Standard node spawner behavior, only we construct the objects
        // using the registry data.
        // NodeRegistry is a map, so we need the value.
        nodos::NodeDescription Desc = NodeRegistry[NodeName];

        // Create node object and pass the type name.
        s_Nodes.emplace_back(GetNextId(), Desc.Type.c_str());

        // Handle creating the pins
        for(nodos::PinDescription p : Desc.Inputs)
            s_Nodes.back().Inputs.emplace_back(GetNextId(), p.Label.c_str(), PinType::Flow);
        for(nodos::PinDescription p : Desc.Outputs)
            s_Nodes.back().Outputs.emplace_back(GetNextId(), p.Label.c_str(), PinType::Flow);

        Desc.InitializeDefaultProperties(s_Nodes.back().Properties);

        // Standard scrubber from examples.
        BuildNode(&s_Nodes.back());

        // "return" value from example spawner
        return &s_Nodes.back();
    }


};

#endif // NODOS_SESSION_DATA_H
