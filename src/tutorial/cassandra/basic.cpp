/**
 * Cassandra client samples
 * Github: https://github.com/datastax/cpp-driver
 * Document: https://docs.datastax.com/en/developer/cpp-driver/2.17/topics/
 */
#include "iostream"
#include <cassandra.h>
#include "gflags/gflags.h"

DEFINE_string(hosts, "127.0.0.1", "cassandra hosts");
DEFINE_string(query, "SELECT release_version FROM system.local", "cassandra query");

int main() {
    /* Setup and connect to cluster */
    CassFuture *connect_future = nullptr;
    CassCluster *cluster = cass_cluster_new();
    CassSession *session = cass_session_new();

    /* Add contact points */
    cass_cluster_set_contact_points(cluster, FLAGS_hosts.c_str());

    /* Provide the cluster object as configuration to connect the session */
    connect_future = cass_session_connect(session, cluster);

    if (cass_future_error_code(connect_future) == CASS_OK) {
        CassFuture *close_future = nullptr;

        /* Build statement and execute query */
        CassStatement *statement = cass_statement_new(FLAGS_query.c_str(), 0);

        CassFuture *result_future = cass_session_execute(session, statement);

        if (cass_future_error_code(result_future) == CASS_OK) {
            /* Retrieve result set and get the first row */
            const CassResult *result = cass_future_get_result(result_future);
            const CassRow *row = cass_result_first_row(result);

            if (row) {
                const CassValue *value = cass_row_get_column_by_name(row, "release_version");

                const char *release_version;
                size_t release_version_length;
                cass_value_get_string(value, &release_version, &release_version_length);
                printf("release_version: '%.*s'\n", (int) release_version_length, release_version);
            }

            cass_result_free(result);
        } else {
            /* Handle error */
            const char *message;
            size_t message_length;
            cass_future_error_message(result_future, &message, &message_length);
            fprintf(stderr, "Unable to run query: '%.*s'\n", (int) message_length, message);
        }

        cass_statement_free(statement);
        cass_future_free(result_future);

        /* Close the session */
        close_future = cass_session_close(session);
        cass_future_wait(close_future);
        cass_future_free(close_future);
    } else {
        /* Handle error */
        const char *message;
        size_t message_length;
        cass_future_error_message(connect_future, &message, &message_length);
        fprintf(stderr, "Unable to connect: '%.*s'\n", (int) message_length, message);
    }

    cass_future_free(connect_future);
    cass_cluster_free(cluster);
    cass_session_free(session);

    return 0;
}