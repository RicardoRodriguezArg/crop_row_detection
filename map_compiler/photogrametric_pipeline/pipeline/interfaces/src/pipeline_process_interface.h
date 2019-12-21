#pragma once
namespace NSFeatureExtraction
{
struct IPipelineProcess
{
virtual ~IPipelineProcess()= default;
virtual void execute() =0;
};
}