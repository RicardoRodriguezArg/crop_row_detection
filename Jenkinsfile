pipeline {
    agent any

    stages {
        stage('Build Map Compiler Site') {
            steps {
                dir('map_compiler/website')
                {
                echo 'Building Python WebSite'
                sh 'python setup.py sdist'

                }
                
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Ansible Deploy') {

            steps {
                echo 'Executing Deploying Scripts'
                dir('scripts')
                {
                    echo 'Preparing Map compiler enviroment'
                    echo 'Applying execution rigths'
                    sh 'chmod +x ./deploy_with_ansible.sh'
                    echo 'Calling Ansibles scritps'
                    sh './deploy_with_ansible.sh'
                }//close Dir
            }//close steps
        }//close Stage
    }//close Stages
}//close Pipeline
