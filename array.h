/*
Copyright (c) 2015-2016, Intel Corporation

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once

#include "type.h"

extern unsigned int MAX_ARRAY_SIZE;
extern unsigned int MIN_ARRAY_SIZE;

class Array {
    public:
        explicit Array () : type(NULL) {};
        explicit Array (std::string _name, unsigned int _type_id, unsigned int _ess_id, unsigned int _size);
        std::string get_name () const;
        void set_iter_name (std::string _iter_name);
        std::string get_iter_name ();
        void set_size (unsigned int _size);
        unsigned int get_size () const;
        std::shared_ptr<Type> get_type ();
        unsigned int get_type_id () const;
        std::string get_type_name () const;
        void set_max_value (uint64_t _max_val);
        uint64_t get_max_value () const;
        void set_min_value (uint64_t _min_val);
        uint64_t get_min_value () const;
        void set_bound_value (std::vector<uint64_t> bval);
        std::vector<uint64_t> get_bound_value () const;
        bool get_is_fp () const;
        bool get_is_signed () const;
        void set_modifier (unsigned int _mod);
        unsigned int get_modifier ();
        void set_is_static (bool _stat);
        bool get_is_static ();
        void set_essence (unsigned int _ess);
        unsigned int get_essence ();
        std::string emit_definition (bool rand_init);
        std::string emit_usage ();
        std::string emit_declaration (bool is_extern);
        static Array get_rand_obj (std::string _name, std::string _iter_name, unsigned int arr_ess);
        void dbg_dump ();

    public:
        enum Mod {
            NTHNG,
            CONST,
            VOLAT,
            CONST_VOLAT,
            MAX_MOD
        };

        enum Ess {
            C_ARR,
            STD_ARR,
            STD_VEC,
            MAX_ESS
        };
    private:
        std::string name;
        std::string iter_name;
        unsigned int essence;
        unsigned int modifier;
        bool is_static;
        unsigned int size;
        std::shared_ptr<Type> type;
};