/**
 * Copyright (c) 2023 Peking University and Peking University
 * Changsha Institute for Computing and Digital Economy
 *
 * CraneSched is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of
 * the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 */

#pragma once

#include <grpc++/grpc++.h>
#include <spdlog/fmt/bundled/format.h>

struct TlsCertificates {
  std::string DomainSuffix;
  std::string ServerCertFilePath;
  std::string ServerCertContent;
  std::string ServerKeyFilePath;
  std::string ServerKeyContent;
};

void ServerBuilderSetCompression(grpc::ServerBuilder* builder);

void ServerBuilderSetKeepAliveArgs(grpc::ServerBuilder* builder);

void ServerBuilderAddUnixInsecureListeningPort(grpc::ServerBuilder* builder,
                                               const std::string& address);

void ServerBuilderAddTcpInsecureListeningPort(grpc::ServerBuilder* builder,
                                              const std::string& address,
                                              const std::string& port);

void ServerBuilderAddTcpTlsListeningPort(grpc::ServerBuilder* builder,
                                         const std::string& address,
                                         const std::string& port,
                                         const TlsCertificates& certs);

void SetGrpcClientKeepAliveChannelArgs(grpc::ChannelArguments* args);

void SetTlsHostnameOverride(grpc::ChannelArguments* args,
                            const std::string& hostname,
                            const TlsCertificates& certs);

std::shared_ptr<grpc::Channel> CreateUnixInsecureChannel(
    const std::string& socket_addr);

std::shared_ptr<grpc::Channel> CreateTcpInsecureChannel(
    const std::string& address, const std::string& port);

std::shared_ptr<grpc::Channel> CreateTcpInsecureCustomChannel(
    const std::string& address, const std::string& port,
    const grpc::ChannelArguments& args);

std::shared_ptr<grpc::Channel> CreateTcpTlsCustomChannelByIp(
    const std::string& ip, const std::string& port,
    const TlsCertificates& certs, const grpc::ChannelArguments& args);

std::shared_ptr<grpc::Channel> CreateTcpTlsChannelByHostname(
    const std::string& hostname, const std::string& port,
    const TlsCertificates& certs);

std::shared_ptr<grpc::Channel> CreateTcpTlsCustomChannelByHostname(
    const std::string& hostname, const std::string& port,
    const TlsCertificates& certs, const grpc::ChannelArguments& args);
