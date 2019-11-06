#!/bin/bash
echo $USER
sudo -u ci_operator ansible-playbook --user -i ci_operator /etc/ansible/hosts ../playbook/playbook.yml -K --key-file /home/ci_operator/.ssh/id_rsa