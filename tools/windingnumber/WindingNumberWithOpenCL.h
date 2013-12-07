#pragma once
#include <string>
#include <Misc/OpenCLWrapper.h>
#include "WindingNumber.h"

class WindingNumberWithOpenCL : public WindingNumber, public OpenCLWrapper {
    public:
        WindingNumberWithOpenCL();
        virtual ~WindingNumberWithOpenCL() {}

    public:
        virtual void init(const MatrixFr& V, const MatrixIr& F);
        virtual VectorF compute(const MatrixFr& P);

    private:
        size_t compute_work_load_partition(size_t num_items, size_t& dim,
                size_t* global_size, size_t* local_size);
        FloatArray pad_floats(size_t desired_size, size_t num_entries, const Float* data);

        template<typename Derived>
        bool is_row_major(const Eigen::MatrixBase<Derived>& M) {
            return M.IsRowMajor;
        }

    private:
        std::string m_kernel_file;
        size_t m_num_vertices;
        size_t m_num_faces;
        cl_mem m_vertex_buf;
        cl_mem m_face_buf;
        cl_mem m_winding_num_buf;
};
