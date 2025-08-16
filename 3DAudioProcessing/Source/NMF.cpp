/*
  ==============================================================================

    NMF.cpp
    Created: 16 Aug 2025 9:24:33pm
    Author:  iiiishii

  ==============================================================================
*/

#include "NMF.h"




/*
//反復更新
for (int i = 0; i < numIterations; ++i)
{
  //再構成行列の計算
    Eigen::MatrixXf lambda = W_ * H_;
    lambda = lambda.cwiseMax(epsilon_);//ゼロ除算防止
  //H の更新
  //分子
    Eigen::MatrixXf h_numerator = W_.transpose() * (targetMatrix.array() / lambda.array().square()).matrix();
 //分母
    Eigen::MatrixXf h_denominator = W_.transpose() * (ones.array() / lambda.array()).matrix();
    h_denominator = h_denominator.cwiseMax(epsilon_);
    H_ = H_.array() * (h_numerator.array() / h_denominator.array());
    H_ = H_.cwiseMax(epsilon_);
 //基底更新前の再計算
    lambda = W_ * H_;
    lambda = lambda.cwiseMax(epsilon_);

  //基底Ｗの更新
  //分子
  Eigen::MatrixXf w_numerator = (targetMatrix.array() / lambda.array().square()).matrix() *
  H_.transpose();
  //分母
  Eigen::MatrixXf w_denominator = (ones.array() / lambda.array()).matrix() * H_.transpose();
  w_denominator = w_denominator.cwiseMax(epsilon_);
  W_ = W_.array() * (w_numerator.array() / w_denominator.array());
  W_ = W_.cwiseMax(epsilon_);
  //正規化
  for (int k = 0; k < numComponents_; ++k) {
    float norm = W_.col(k).norm();
    if (norm > epsilon_) {
      W_.col(k) /= norm;
      H_.row(k) *= norm;
    }
  }
}

Eigen::MatrixXf centeredSignals =
 inputSignals.colwise() 
inputSignals.rowwise().mean();

//共分散行列
    Eigen::MatrixXf covariance =
 (centeredSignals *
 centeredSignals.transpose()) / (numSamples 
1);
 //固有値分解
Eigen::SelfAdjointEigenSolver<Eigen::MatrixXf>
 eigenSolver(covariance);
    Eigen::MatrixXf D =
 eigenSolver.eigenvalues().asDiagonal();
    Eigen::MatrixXf E =
 eigenSolver.eigenvectors();


  //平方根
    for (int i = 0; i < D.rows(); ++i)
        D(i, i) = 1.0f / std::sqrt(D(i, i) +
 epsilon_);
    // 白色化行列と、白色化された信号を計算
    Eigen::MatrixXf whiteningMatrix = E * D
 * E.transpose();
    Eigen::MatrixXf whitenedSignals =
 whiteningMatrix * centeredSignals;


  //乱数で初期化
     Eigen::MatrixXf W =
 Eigen::MatrixXf::Random(numComponents,
 numComponents);
    
    //初期直交化
    //SVDを利用
    Eigen::JacobiSVD<Eigen::MatrixXf> svd(W,
 Eigen::ComputeThinU | Eigen::ComputeThinV);
    W = svd.matrixU() *
 svd.matrixV().transpose();
    //g(u) = tanh(u)とその導関数g'(u) = 1 
tanh(u)^2
    //非ガウス性の評価に使う
    auto g = [](float u) { return
 std::tanh(u); };
    auto g_prime = [](float u) { return 1.0f- std::tanh(u) * std::tanh(u); };
    //反復更新
    for (int iter = 0; iter < maxIterations;
 ++iter)
    {
        Eigen::MatrixXf W_old = W;
        //Wの更新
        Eigen::MatrixXf G_WX = (W * 
            whitenedSignals).unaryExpr(g);
        Eigen::MatrixXf G_prime_WX_mean 
        = (W * whitenedSignals)
            .unaryExpr(g_prime)
            .rowwise().mean();
        Eigen::MatrixXf W_new = (G_WX *
 whitenedSignals.transpose()) / numSamples;
        W_new -=
 G_prime_WX_mean.asDiagonal() * W;
        //対称直交化
Eigen::SelfAdjointEigenSolver<Eigen::MatrixXf>
 eigenSolverW(W_new * W_new.transpose());
        Eigen::MatrixXf D_W_inv_sqrt 
        = eigenSolverW.eigenvalues()
            .cwiseInverse().cwiseSqrt()
            .asDiagonal();
        Eigen::MatrixXf E_W =
 eigenSolverW.eigenvectors();
        W = E_W * D_W_inv_sqrt *
 E_W.transpose() * W_new;
        
        //収束判定
        //更新前後で行ベクトルの向きが変わらなく
なったか、内積を用いて判定
        float max_diff = 0.f;
        for (int i = 0; i < W.rows(); ++i) {
            max_diff = std::max(max_diff,
 std::abs(std::abs((W.row(i) *
 W_old.row(i).transpose()).value()) - 1.0f));
        }
        
        if (max_diff < tolerance)
        {
            break;
        }
    }

。
//分離した数だけ処理のインスタンスを生成
for (int i = 0; i <
 separatedAudio.size(); ++i)
 {
 auto* proc = new HRTFProcessor();
        hrtfProcessors.add(proc);
 //スライダーを生成
auto* azSlider = new juce::Slider();
        azimuthSliders.add(azSlider);
 }
 // 指定位置に最も近いHRIRフィルタを取得し、一
時バッファに書き込む
// getfilter はL/Rのペアを取得する
float leftDelay, rightDelay;
 mysofa_getfilter_float(hrtf, pos[0],
 pos[1], pos[2],
        hrirBuffer.getWritePointer(0), // 左
チャンネルの書き込み先
        hrirBuffer.getWritePointer(1), // 右
チャンネルの書き込み先
&leftDelay, &rightDelay);
 //畳み込み
//juce::dsp::Convolution convLeft,
 convRight;
 // 左右チャンネルをそれぞれ処理
// 左チャンネル
auto leftBlock
 = juce::dsp::AudioBlock<float>
 (outputBuffer).getSingleChannelBlock(0);
 juce::dsp::ProcessContextNonReplacing<float>
 contextLeft(inputBlock, leftBlock);
    convLeft.process(contextLeft);
 // 右チャンネル
auto rightBlock 
= juce::dsp::AudioBlock<float>
 (outputBuffer).getSingleChannelBlock(1);
 juce::dsp::ProcessContextNonReplacing<float>
 contextRight(inputBlock, rightBlock);
    convRight.process(contextRight);
 //各分離音源に対して畳み込みを適用して加算
for (int i = 0; i <
 separatedAudio.size(); ++i)
 {
        juce::AudioSampleBuffer
 stereoOutput;
        stereoOutput.setSize(2, numSamples);
        stereoOutput.clear();
 // HRTF 処理でモノラル→ステレオ変換
        hrtfProcessors[i]
>process(*separatedAudio[i], stereoOutput);
 // 最終ミックスに加算
        finalMix.addFrom(0, 0, stereoOutput,
 0, 0, numSamples);
        finalMix.addFrom(1, 0, stereoOutput,
 1, 0, numSamples);
}


*/