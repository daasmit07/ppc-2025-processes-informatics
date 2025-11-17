#include <gtest/gtest.h>

#include "mityaeva_d_min_v_rows_matrix/common/include/common.hpp"
#include "mityaeva_d_min_v_rows_matrix/mpi/include/ops_mpi.hpp"
#include "mityaeva_d_min_v_rows_matrix/seq/include/ops_seq.hpp"
#include "util/include/perf_test_util.hpp"

namespace mityaeva_d_min_v_rows_matrix {

class MityaevaDRunPerfTestsProcesses : public ppc::util::BaseRunPerfTests<InType, OutType> {
  const int kCount_ = 100;
  InType input_data_{};

  void SetUp() override {
    input_data_ = kCount_;
  }

  bool CheckTestOutputData(OutType &output_data) final {
    return input_data_ == output_data;
  }

  InType GetTestInputData() final {
    return input_data_;
  }
};

TEST_P(MityaevaDRunPerfTestsProcesses, RunPerfModes) {
  ExecuteTest(GetParam());
}

const auto kAllPerfTasks = ppc::util::MakeAllPerfTasks<InType, MityaevaDTestTaskMPI, MityaevaDTestTaskSEQ>(
    PPC_SETTINGS_mityaeva_d_min_v_rows_matrix);

const auto kGtestValues = ppc::util::TupleToGTestValues(kAllPerfTasks);

const auto kPerfTestName = MityaevaDRunPerfTestsProcesses::CustomPerfTestName;

INSTANTIATE_TEST_SUITE_P(RunModeTests, MityaevaDRunPerfTestsProcesses, kGtestValues, kPerfTestName);

}  // namespace mityaeva_d_min_v_rows_matrix
