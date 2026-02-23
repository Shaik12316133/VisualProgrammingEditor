#pragma once

enum class NodeType
{
    SayLine,
    Branch,
    ReadVar,
    WriteVar,
    Comparison,
    Math,
    LogicalAND,
    LogicalOR,
    LogicalNOT,
    PickNumber,
    PickString
};
