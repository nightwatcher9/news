package com.hjzf.ui.user

import android.content.Intent
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import androidx.fragment.app.viewModels
import com.app.ui.activity.ChangeInformation
import com.app.ui.activity.ChangePassword
import com.app.ui.activity.Userdo
import com.hjzf.NewsApplication
import com.hjzf.databinding.FragmentUserBinding
import com.hjzf.ui.MainActivity

class UserFragment : Fragment() {

    private val viewModel: UserViewModel by viewModels()

    private var _binding: FragmentUserBinding? = null
    private val binding get() = _binding!!

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentUserBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        viewModel.refresh()
        binding.quit.setOnClickListener {
            var intent = Intent()
            intent.setClass(NewsApplication.context, MainActivity::class.java)
            startActivity(intent)

        }
        binding.changePassword.setOnClickListener {
            var intent = Intent()
            intent.setClass(NewsApplication.context, ChangePassword::class.java)
            startActivity(intent)
        }
        binding.changeinformation.setOnClickListener {
            var intent = Intent()
            intent.setClass(NewsApplication.context,ChangeInformation::class.java)
        }

    }



}